

/*xxx�豸�ṹ��*/
struct xxx_dev
{
struct cdev cdev;
...
timer_list xxx_timer;/*�豸Ҫʹ�õĶ�ʱ��*/
};

/*xxx�����е�ĳ����*/
xxx_func1(...)
{
struct xxx_dev *dev = filp->private_data;
...
/*��ʼ����ʱ��*/
init_timer(&dev->xxx_timer);
dev->xxx_timer.function = &xxx_do_timer;
dev->xxx_timer.data = (unsigned long)dev;
/*�豸�ṹ��ָ����Ϊ��ʱ������������*/
dev->xxx_timer.expires = jiffies + delay;
/*��ӣ�ע�ᣩ��ʱ��*/
add_timer(&dev->xxx_timer);
...
}

/*xxx�����е�ĳ����*/
xxx_func2(��)
{
...
/*ɾ����ʱ��*/
del_timer (&dev->xxx_timer);
...
}

/*��ʱ��������*/
static void xxx_do_timer(unsigned long arg)
{
struct xxx_device *dev = (struct xxx_device *)(arg);
...
/*���ȶ�ʱ����ִ��*/
dev->xxx_timer.expires = jiffies + delay;
add_timer(&dev->xxx_timer);
...
}