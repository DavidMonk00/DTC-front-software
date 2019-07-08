import re
import sys


class HeaderFile:
    def __init__(self, filename):
        self.class_name = ""
        self.methods = []
        self.header_methods = []
        self.filename = filename
        self.file = open(filename, "r")
        self.lines = self.cleanFile()

    def cleanFile(self):
        lines = []
        for line in self.file:
            line = line.strip()
            if line:
                lines.append(line)
        return lines

    def getMethods(self):
        for line in self.lines:
            if line.startswith("class"):
                self.class_name = line.split(" ")[1]
            elif self.class_name != "":
                if "}" in line:
                    break
                else:
                    reg = re.search("[A-Za-z\~]*\ *[A-Za-z\~]*\(.*\)", line)
                    if reg:
                        method_name = reg.group()
                        if "virtual" in method_name:
                            split_method = method_name.split(" ")
                            method_name = (" ").join(split_method[1:])

                        method_name = self.class_name + "::" + method_name + \
                            " {}"
                        if "get" in method_name or "set" in method_name:
                            pass
                        else:
                            self.methods.append(method_name)
        return self.methods

    def generateGettersAndSetters(self):
        for line in self.lines:
            if line.startswith("class"):
                self.class_name = line.split(" ")[1]
            reg = re.search("[A-Za-z\~]*\ [A-Za-z\~]*;", line)
            if reg:
                datum = reg.group()[:-1].split(" ")
                get_method = "%s %s::get%s(void) {\n\treturn %s;\n}" % (
                    datum[0], self.class_name, datum[1].capitalize(), datum[1])
                self.header_methods.append("%s get%s(void);\n" % (
                    datum[0], datum[1].capitalize()
                ))
                self.methods.append(get_method)
                set_method = "void %s::set%s(%s %s_%s) {\n\t%s_%s = %s;\n}" % (
                    self.class_name, datum[1].capitalize(), datum[0],
                    self.class_name, datum[1], self.class_name, datum[1],
                    datum[1])
                self.header_methods.append("void set%s(%s %s_%s);\n" % (
                    datum[1].capitalize(), datum[0], self.class_name,
                    datum[1]
                ))
                self.methods.append(set_method)

        print("Add these methods to your header file if they do not " +
              "already exist:\n")
        print(("").join(self.header_methods))

    def constructSourceFile(self):
        if len(self.methods) == 0:
            self.getMethods()
            self.generateGettersAndSetters()

        header_name = re.search("[A-Za-z]*\.hpp$", self.filename).group()
        self.src_name = "./src/" + \
            re.search("[A-Za-z]*\.", header_name).group() + "cpp"

        self.src = '#include "' + header_name + '"\n\n'
        for method in self.methods:
            self.src += method + "\n\n"

        with open(self.src_name, "w") as f:
            f.write(self.src)


def main():
    if len(sys.argv > 1):
        header = HeaderFile(sys.argv[1])
        header.constructSourceFile()


if __name__ == '__main__':
    main()
