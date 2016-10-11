#ifndef SCENE
#define SCENE
//场景类
class Scene{
protected:
	int type;//类型
public:
	Scene(){};//构造函数
	virtual bool initialize(){return true;};//初始化函数
	int get_type(){return type;}//得到场景类型
	virtual bool logic_update(){return false;}
	virtual bool render(){return false;}//绘制函数
	virtual bool change(){return false;}//逻辑更新
	virtual int get_change_type(){return false;}//得到应该转换的场景
	virtual int get_change_information(){return 0;};//得到转换时传递的信息
	virtual bool is_changing(){return false;}//判断是否正在转换
	virtual ~Scene(){}//析构函数
	virtual float get_gap(){return 0;}//得到当前已经转换了多久
};

#endif