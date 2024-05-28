import os

path = "../Codigos"
latex_file_name = "capi-lib.tex"
dir_list = os.listdir(path)
latex_file = open(latex_file_name,"w")

def write_subsection(file,file_path):
    code_name,language = file.split('.')
    subsection=f"\subsection{{{code_name}}}\n"
    latex_file.write(subsection)
    latex_file.write(f"\\begin{{minted}}{{{language}}}\n\n")
    f = open(file_path,'r')
    for line in f:
        latex_file.write(line)
    f.close()
    latex_file.write(f"\end{{minted}}\n\n")

def write_sections(directory,directory_path):
    section = f"\section{{{directory}}}\n"
    latex_file.write(section)
    directory_path = path+'/'+directory+'/'
    files = os.listdir(directory_path)
    for file in files:
        write_subsection(file,directory_path+'/'+file)


#Write init o latex lib
init_latex = open('init.tex','r')
for line in init_latex:
    latex_file.write(line)
init_latex.close()

#Write sections
for directory in dir_list:
    write_sections(directory,path+'/'+directory+'/')

#Write end o latex lib
end_latex = open('end.tex','r')
for line in end_latex:
    latex_file.write(line)
end_latex.close()
        


