# cpp-init-repo-template

cpp-init-repo-template

## Env

```bash
conda install cmake ninja clang-format clang-tools -y -c conda-forge
```

- `.vscode/cmake-kits.json`

```json
    "compilers": {
      "C": "<change your own cpp compiler>",
      "CXX": "<change your own cpp compiler>"
    },
```

- `.vscode/settings.json`

```json
  "cmake.cmakePath": "<your own cmake path in conda>",
```

- `.vscode/.envsetup.sh`

```bash
# source <your conda installation dir>/etc/profile.d/conda.sh && conda activate <env_name>
```

if you manage your environments with conda and compiler is clang

you need to install with commands:

```bash
conda install clang clangxx libstdcxx-devel_linux-64 libgcc-devel_linux-64 -c conda-forge -y
```
