cp .vimrc ~/

sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116

echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc

sudo apt update

# Install program required for project
sudo apt install tmux xterm libignition-math2-dev protobuf-compiler ros-kinetic-desktop-full python-pyqt5 python-pyside python-rosinstall python-rosinstall-generator python-wstool build-essential -y
pip install catkin_pkg
pip install empy
pip install pyyaml
pip install rospkg
python3 -m pip install PyQt5

# switch to python2.7
mv /root/miniconda3/bin/python /root/miniconda3/bin/oldpython
ln -s /usr/bin/python2.7 /root/miniconda3/bin/python

# Configure git
git config --global user.email "djhawbaker@gmail.com"
git config --global user.name "David Hawbaker"

. ~/.bashrc

tmux
