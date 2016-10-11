#ifndef SCENE
#define SCENE
//������
class Scene{
protected:
	int type;//����
public:
	Scene(){};//���캯��
	virtual bool initialize(){return true;};//��ʼ������
	int get_type(){return type;}//�õ���������
	virtual bool logic_update(){return false;}
	virtual bool render(){return false;}//���ƺ���
	virtual bool change(){return false;}//�߼�����
	virtual int get_change_type(){return false;}//�õ�Ӧ��ת���ĳ���
	virtual int get_change_information(){return 0;};//�õ�ת��ʱ���ݵ���Ϣ
	virtual bool is_changing(){return false;}//�ж��Ƿ�����ת��
	virtual ~Scene(){}//��������
	virtual float get_gap(){return 0;}//�õ���ǰ�Ѿ�ת���˶��
};

#endif