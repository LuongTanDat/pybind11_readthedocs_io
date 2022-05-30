# g++

```bash
c++ -O3 -Wall -shared -std=c++2a -fPIC $(python3-config --includes) -Iextern/pybind11/include op.cpp -o warp$(python3-config --extension-suffix)
```

# `setup.py`

```bash
python setup.py clean
python setup.py build_ext -i
```

# Import

```python
import warp
warp.add(1, 2)
warp.sub(1, 2)
warp.mul(1, 2)
warp.div(1, 2)
warp.fourty_two
warp.get_started
```
