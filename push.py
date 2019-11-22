import os
os.system("git pull origin master");
os.system("cd game; doxygen doxygen.conf;");
os.system("cd game/docs/latex; make;");
os.system("git add *");
os.system('git commit -m "' + input("Kommentar: ") + '"');
os.system('git push origin master');
