
# tinyxml2 wrapper class 
- https://github.com/leethomason/tinyxml2.git

## Requirements
- boost header, boost.locale

## Examples

```cpp

using namespace tinyxml2;
tinyxml2::XMLDocument doc;
doc.LoadFile("r.xml");

auto root = doc.RootElement();

auto list = Node(root).Select("/url-group/item");
for (auto &e : list) {
	string name = Node(e).First("name").Text();
	string issue_type = Node(e).First("issue-type").Text();
}

```
