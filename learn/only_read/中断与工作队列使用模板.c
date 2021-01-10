 /*���幤�����к͹�������*/
 struct work_struct xxx_wq;
 void xxx_do_work(unsigned long);

 /*�жϴ���װ벿*/
 void xxx_do_work(unsigned long)
 {
 ...
 }

 /*�жϴ����벿*/
 irqreturn_t xxx_interrupt(int irq, void *dev_id, struct pt_regs��*regs)
{
...
schedule_work(&xxx_wq);
...
}

/*�豸����ģ����غ���*/
int xxx_init(void)
{
...
/*�����ж�*/
result = request_irq(xxx_irq, xxx_interrupt,SA_INTERRUPT, "xxx", NULL);
...
/*��ʼ����������*/
INIT_WORK(&xxx_wq, (void (*)(void *)) xxx_do_work, NULL);
...
}

/*�豸����ģ��ж�غ���*/
void xxx_exit(void)
{
...
/*�ͷ��ж�*/
free_irq(xxx_irq, xxx_interrupt);
...
}