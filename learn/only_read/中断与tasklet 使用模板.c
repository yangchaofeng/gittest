

/*����tasklet�͵װ벿����������*/
void xxx_do_tasklet(unsigned long);
DECLARE_TASKLET(xxx_tasklet, xxx_do_tasklet, 0);

/*�жϴ���װ벿*/
void xxx_do_tasklet(unsigned long)
{
...
}

/*�жϴ����벿*/
irqreturn_t xxx_interrupt(int irq, void *dev_id, struct pt_regs��*regs)
{
...
tasklet_schedule(&xxx_tasklet);
...
}

/*�豸����ģ����غ���*/
int __init xxx_init(void)
{
...
/*�����ж�*/
result = request_irq(xxx_irq, xxx_interrupt,SA_INTERRUPT, "xxx", NULL);
...
}

/*�豸����ģ��ж�غ���*/
void __exit xxx_exit(void)
{
...
/*�ͷ��ж�*/
free_irq(xxx_irq, xxx_interrupt);
...
}