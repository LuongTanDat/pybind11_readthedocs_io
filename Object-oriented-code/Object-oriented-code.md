# g++

```bash
c++ -O3 -Wall -shared -std=c++2a -fPIC $(python3-config --includes) -Iextern/pybind11/include oop-code.cpp -o oop_warp$(python3-config --extension-suffix)
```

# `setup.py`

```bash
python setup.py clean
python setup.py build_ext -i
```

# Import

```python
import oop_warp

ps = oop_warp.PetStruct("Molly")
print(ps, ps.name)
ps.age = 2
ps.age
ps.getName()
ps.setName("Charly")
ps.getName()

pc = oop_warp.PetClass("Molly")
print(pc, pc.name)
pc.setName("Charly")
pc.name

pc.name = "Molly"
pc.name
pc.attr1 = 1.1
pc.attr2

dog = oop_warp.Dog("con choa'")
dog
dog.bark()

cat = oop_warp.Cat("meo lon")
cat
cat.meow()

p2 = oop_warp.PetStruct2("Lucy", oop_warp.PetStruct2.Cat)
p2.type
int(p2.type)
oop_warp.PetStruct2.Kind.__members__
```
