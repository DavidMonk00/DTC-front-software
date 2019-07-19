import re
import json
from glob import glob


tools_path = "/home/dmonk/Software/DTC-front/tools/"

class BoilerPlate:
    def __init__(self, metadata_file, filepath):
        self.exists = False
        try:
            reg = re.search(r"[a-zA-Z]*\.[ch]pp$", filepath)
            self.filename = reg.group()
        except AttributeError:
            print(filepath)
            raise Exception("Filename is not a C++ header or source file.")
        self.filepath = filepath
        self.metadata = json.load(open(metadata_file))
        with open(tools_path + "boilerplate.txt") as bp_f:
            self.boilerplate = bp_f.read()

    def generate(self):
        self.boilerplate = re.sub(
            "<filename>",
            self.filename,
            self.boilerplate)
        self.boilerplate = re.sub(
            "<author>",
            self.metadata["author"],
            self.boilerplate)
        self.boilerplate = re.sub(
            "<institution>",
            self.metadata["institution"],
            self.boilerplate)
        return self.boilerplate

    def checkFileForExisting(self):
        file = open(self.filepath)
        f_str = file.read()
        file.close()
        f_str = f_str.replace('\n', '')
        reg = re.search(r"\/\*.*Filename.*Author.*\*\/", f_str)
        if (reg):
            self.exists = True
        

    def addToFile(self):
        self.checkFileForExisting()
        if (not self.exists):
            self.generate()
            file = open(self.filepath)
            f_str = file.read()
            file.close()
            f_str = self.boilerplate + f_str
            file = open(self.filepath, "w")
            file.write(f_str)
            file.close()


def main():
    files = glob("/home/dmonk/Software/DTC-front/*/*")
    for i in files:
        if (re.search(r"\.[ch]pp$", i)):
            bp = BoilerPlate(tools_path + "metadata.json", i)
            bp.addToFile()
            




if __name__ == "__main__":
    main()