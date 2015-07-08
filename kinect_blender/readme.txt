sudo adduser $USER plugdev
apt-get install libav-tools freenect freeglut3-dev libusb-1.0-0-dev libopencv-deb
g++ -I /usr/include/libusb-1.0 -o cppview cppview.cpp -lfreenect -lusb-1.0 -l pthread -lGL -lGLU -lglut

git :

git config --global user.name "killwiner"
git config --global user.email "alex.arranhado@gmail.com"

cd tron
git init

# git status
git add folder
git commit -m "ajout du projet"
git remote add origin https://github.com/killwiner/tron.git
# git remote -v
git push origin master

git status
git rm fichier
git add .
git commit -m "message"
git push

git clone https://github.com/killwiner/tron.git tron
