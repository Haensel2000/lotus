#include <lotus.h>
#include <dxr.h>
#include <iostream>
#include <string>

using namespace Lotus;
using namespace DX;
using namespace std;

class Test
{
private:
	Array<Geometry*> m_arr;
public:
	static const int ARRAY_SIZE = 257;
	static const int ARRAY_GROW = 256;
	Test() : m_arr(ARRAY_SIZE, ARRAY_GROW) {}
};

class Test2 : public Test
{
public:
	Test2() : Test() {}
};

int main()
{
	
	/*List<Adapter>& disp = DXRenderer::GetDisplayConfigurations();
	for (List<Adapter>::Iterator i = disp.begin(); i != false; i++)
	{
		cout << i->name << ": " << endl;
		for (List<DisplayConfiguration>::Iterator j = i->displayConfigurations.begin(); j != false; j++)
		{
			cout << "   " << j->getWidth() << "x" << j->getHeight() << "x" << j->getRefreshRate() << endl;
		}
	}*/

	GeometryBatch* ib = new IterateBatch(0, 0);

	return 0;
}