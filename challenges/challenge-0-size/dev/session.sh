#doitlive shell: /bin/bash
#doitlive prompt: default
#doitlive speed: 1
#doitlive env: DOCS_URL=https://doitlive.readthedocs.io
#doitlive commentecho: true

git clone git@github.com:Perfexionists/perun-demo.git
cd perun-demo/challenges
git init; git first

vf new -p (which python3.11) pydemo
pip3 install perun-toolsuite
perun --version

perun init
perun status
ls -al

cd challenge-0-size/
make
./squared_count inputs/small-random.txt

perun collect -c "./squared_count inputs/small-random.txt" kperf
make
perun collect -c "./squared_count inputs/small-random.txt" kperf
perun status
perun showdiff --offline 0@p 1@p report --minimize -o diff