# LeetCode Interview

## ENV with conda (GLIBCXX >= 3.4.29)

```bash
conda create -n cpp-simplecode python=3.10 libstdcxx-ng=12 gxx=12.* gcc=12.* gdb=12.* gxx_linux-64==12.* cmake ninja fmt=10.* -y -c conda-forge
conda activate cpp-simplecode
```

## Generating `NOTE.md`

- Install Dependencies:

```bash
pip3 install python-leetcode markdownify tqdm
```

- Set the environment variable `LEETCODE_SESSION` to your leetcode session cookie. or save the session cookie to `.leetcode_session`.
The cookie can be found in the browser after you login to leetcode.
you can find by `Chrome` -> `F12` -> `Application` -> `Storage` -> `Cookies` -> `https://leetcode.com` -> `LEETCODE_SESSION`.

- Run `python3 tools/populate_notes.py` to generate `NOTE.md` under the same directory with `README.md`.

- (Optional) Right click and format the mardown file with `markdownlint` in `VSCode`.
