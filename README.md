# ppii2-STTV

## To run the project

Please clone the repository 

```bash
git clone https://gitlab.telecomnancy.univ-lorraine.fr/ppii2_2223/ppii2-grp_18
```

cd into the project folder

```bash
cd ppii2-grp_18
```

install the pip dependencies

```bash
pip install -r requirements.txt
```


run the pyhthon script to clear the database

```bash
python3 utils/borne_cleaner.py
```
create the `bin` directory

```bash
mkdir bin
```


then run 

```bash
make
```

to build the project.

You can now run any executable including the tests. Some of them may present memory leaks, but the main application does not.


