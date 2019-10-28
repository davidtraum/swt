import os
os.system("git pull origin master");
os.system("cd prototype; doxygen doxygen.conf;");
os.system("cd prototype/docs/latex; make;");
os.system("git add *");
os.system('git commit -m "' + input("Kommentar: ") + '"');
os.system('git push origin master');
