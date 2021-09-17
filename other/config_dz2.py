import requests
import json
from itertools import chain


class Parser:
    requirements = {}

    def __init__(self, package: str):
        # parse_package
        json = self.get_response(package)
        self.parse_json(json, package)

    def get_response(self, package: str):
        base_url = "https://pypi.org/pypi/{}/json?callback="
        headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36'}

        response = requests.get(base_url.format(package), headers=headers, timeout=5)
        if response.ok:
            return response.json()

        return None

    def parse_package(self, package: str) -> dict:
        pass

    def parse_json(self, json: dict, current_package: str) -> None:
        if json is None:
            return

        package_info = json['info']

        if 'requires_dist' in package_info and package_info['requires_dist']:
            if current_package not in self.requirements:
                self.requirements[current_package] = []
            
            requires = package_info['requires_dist']
            requires_packages = [item.split()[0] for item in requires if "extra" not in item]

            self.requirements[current_package].append( 
                [item for item in requires_packages if item != current_package]
            )

            for package_name in requires_packages:
                if package_name != current_package:
                    new_json = self.get_response(package_name)
                    self.parse_json(new_json, package_name)

    def get_requirements(self) -> dict:
        cleaned_requirements = {}
        for req_key in self.requirements:
            cleaned_requirements[req_key] = list(set(chain(*self.requirements[req_key])))

        return cleaned_requirements

    def get_graphviz_code(self) -> str:
        requirements = self.get_requirements()
        code = ""

        for req_key in requirements:
            for package in requirements[req_key]:
                code += f'"{req_key}" -> "{package}\n'

        return code


if '__main__' == __name__:
    package = input().strip(" ")
    parser = Parser(package)
    print(parser.get_graphviz_code())
