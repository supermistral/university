import requests, zipfile, io, tarfile, sys, re
from requests import Response


class Parser:
    requirements        = {}
    headers             = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36'}
    base_json_url       = "https://pypi.org/pypi/{}/json"
    package_extra       = {'sys_platform': sys.platform,
                           'python_version': sys.version}
    archive_supported   = {}
    user_extra          = []


    def __init__(self, package: str) -> None:
        self.archive_supported = {'whl': ('.whl', Parser.handle_whl, self.parse_whl),
                                  'gzip': ('.tar.gz', Parser.handle_gzip, self.parse_gzip_zip),
                                  'zip': ('.zip', Parser.handle_zip, self.parse_gzip_zip)}

        try:
            self.parse_archive(self.parse_user_package(package))
        except Exception as e:
            print("[ERROR] ", e)


    def get_json(self, package: str) -> dict or None:
        response = requests.get(self.base_json_url.format(package), headers=self.headers)
        
        if response.ok:
            return response.json()
        
        return None


    def parse_user_package(self, package_str: str) -> str:
        if '[' in package_str and ']' in package_str:
            package, extra = package_str.split('[')
            self.user_extra = [e for e in extra.rstrip(']').split(',')]
        else:
            package = package_str
        
        return package


    def parse_requires_archive(self, response: Response, mode: str = "whl") -> list or None:
        target_content = self.archive_supported[mode][1](response)

        if target_content is None:
            return None

        requires = self.archive_supported[mode][2](target_content)
        return requires


    def get_requires_by_url(self, url: str, mode: str = "whl") -> list or None:
        print("[Download] " + url, end=" ")
        response = requests.get(url, headers=self.headers, stream=True)
        print(response.status_code)

        if response.ok:
            return self.parse_requires_archive(response, mode)
        
        return None


    def parse_archive(self, current_package: str) -> None:
        json = self.get_json(current_package)
        
        if json is None:
            return

        print("\n[Parsing] " + current_package)

        url_list        = json['urls'][::-1]
        url_whl_list    = list(filter(
                            lambda x: x["url"].endswith(self.archive_supported['whl'][0]), 
                            url_list))
        requires        = None

        # Парсинг единственного whl 
        if len(url_whl_list) == 1:
            requires = self.get_requires_by_url(url_whl_list[0]["url"], 'whl')

        # whl не один или парсинг whl не дал результата - попытка в gzip (или zip)
        if requires is None:
            for url_data in url_list:
                archive_url = url_data["url"]
                if archive_url.endswith(self.archive_supported['gzip'][0]):
                    requires = self.get_requires_by_url(archive_url, 'gzip')
                    break
                elif archive_url.endswith(self.archive_supported['zip'][0]):
                    requires = self.get_requires_by_url(archive_url, 'zip')
                    break

        # gzip/zip не дали результатов - попытка в какой-нибудь whl 
        # (по-хорошему нужно искать в что-то похожее на OS, откуда запускается скрипт)
        if requires is None:
            requires = self.get_requires_by_url(url_whl_list[0]['url'], 'whl')
        
        # Ничего не найдено
        if requires is None:
            raise ValueError("Archive not found")

        self.requirements[current_package] = requires

        for req_package in requires:
            try:
                self.parse_archive(req_package)
            except Exception as e:
                print("[ERROR] ", e)


    @staticmethod
    def handle_gzip(response: Response) -> str or None:
        with tarfile.open(fileobj=io.BytesIO(response.raw.read()), mode="r:gz") as tar:
            for member in tar.getmembers():
                if member.name.endswith('requires.txt'):
                    f = tar.extractfile(member)
                    if f is not None:
                        print("[Requires.txt] Found -> " + member.name)
                        return str(f.read(), 'utf-8')

        return None


    @staticmethod
    def handle_zip(response: Response) -> str or None:
        z = zipfile.ZipFile(io.BytesIO(response.content))
        for zip_name in z.namelist():
            if zip_name.endswith('requires.txt'):
                print("[Requires.txt] Found -> " + zip_name)
                return str(z.read(zip_name), 'utf-8')

        return None


    @staticmethod
    def handle_whl(response: Response) -> str or None:
        z = zipfile.ZipFile(io.BytesIO(response.content))
        for zip_name in z.namelist():
            if zip_name.endswith("METADATA"):
                print("[Metadata] Found -> " + zip_name)
                return str(z.read(zip_name), 'utf-8')

        return None


    def parse_gzip_zip(self, content: str) -> list:
        res_full_requires = []
        cond_result = True

        for req_row in content.split("\n"):
            if req_row:           
                if req_row.startswith("[") and req_row.endswith("]"):
                    args = req_row.lstrip("[").rstrip("]").split(":")
                    key, cond = args if len(args) == 2 else [args, '']
                    
                    if cond:
                        context = {'cond_result': cond_result, **self.package_extra}
                        exec("cond_result=" + cond, None, context)
                        cond_result = context['cond_result'] and key in self.user_extra \
                                        if (key and self.user_extra) \
                                        else context['cond_result']
                    else:
                        cond_result = key in self.user_extra if self.user_extra else False
                elif cond_result:
                    res_full_requires.append(req_row)

        res_requires = [re.match(r'[\w|-]+', req).group(0) for req in res_full_requires]
        return res_requires


    def parse_whl(self, content: str) -> list:
        res_requires = []

        req_pattern = r"Requires-Dist\:\s*(\S+)(.+;\s*(\S.+))?"
        matches = re.findall(req_pattern, content)

        for match in matches:
            key, cond = match[0], match[2] if len(match) == 3 else [match[0], '']
            cond_result = True

            if cond:
                cond_result = False
                context = {'cond_result': cond_result, 'extra': '', **self.package_extra}
                if self.user_extra:
                    for extra in self.user_extra:
                        context['extra'] = extra
                        exec("cond_result=" + cond, None, context)
                        if context['cond_result']:
                            break
                else:
                    exec("cond_result=" + cond, None, context)

                cond_result = context['cond_result']
                
            if cond_result:
                res_requires.append(key)
        
        return res_requires


    def get_graphviz_code(self) -> str:
        code = ""

        for req_key in self.requirements:
            for package in self.requirements[req_key]:
                code += f'"{req_key}" -> "{package}"\n'

        return "digraph G {\n" + code + "}"


if  __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Package name expected. Type 'python <module name> <package name>'")
        exit()
        
    parser = Parser(sys.argv[1])
    print("\n\n", parser.get_graphviz_code())
