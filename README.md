# hey there !

[Simple circles colliding the walls (only walls)](https://github.com/zairysbigtae/Basic-Bouncing-Circles/tree/main/Simple)

[Collision With Each Other](https://github.com/zairysbigtae/Basic-Bouncing-Circles/tree/main/CollisionWithEachOther)

so i want to tell you something here, i want to make this repository as my project that i will be doing every day, every week.

so if you can, you could help me by contributing if you want to! although ive actually never tried contributions on github before..

and fun fact: this is my first repository with .git haha

### How to run it

```
git clone --depth 1 --filter=blob:none --sparse https://github.com/zairysbigtae/Basic-Bouncing-Circles.git
cd Basic-Bouncing-Circles
git sparse-checkout set all_exes
rm -rf .git
cd all_exes
```
now you can execute whatever simulations youd like!
```
./PingBouncingBalls
```

### Running on different platforms
Are you worried about the game NOT running on other platforms? well say no more because now we have released a web browser version of this game! (android included, just scroll to the bottom of this section)

now just install it using the commands below:
```
git clone --depth 1 --filter=blob:none --sparse https://github.com/zairysbigtae/Basic-Bouncing-Circles.git
cd Basic-Bouncing-Circles
git sparse-checkout set all_webs
rm -rf .git
cd all_webs
```
now you can visit any web-games

##### using python
```
python -m http.server 8080 # any port youd like | 8080 is the common one
```

##### using node
```
npm install -g http-server
http-server
```

##### on android, with termux
you can install [termux](https://f-droid.org/repo/com.termux_1020.apk) (<- click it to install immediately) and use these commands
```
apt update && apt upgrade
apt install node # if you wanna use python, replace node with python
```
keep entering Y to everything and boom, youre done!
now you can use it with [node](#using-node) or [python](#using-python) on termux