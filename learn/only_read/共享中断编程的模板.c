 
 
 /*�жϴ����벿*/
 irqreturn_t xxx_interrupt(int irq, void *dev_id, struct pt_regs��*regs)
 {
 ...
 int status = read_int_status();/*��֪�ж�Դ*/
 if(!is_myint(dev_id,status))/*�ж��Ƿ��Ǳ��豸�ж�*/
 {
 return IRQ_NONE; /*��������*/
 }
 ...
 return IRQ_HANDLED;
 }

 /*�豸����ģ����غ���*/
 int xxx_init(void)
 {
 ...
 /*���빲���ж�*/
 result = request_irq(sh_irq, xxx_interrupt,SA_SHIRQ, "xxx", xxx_dev);//�����жϱ�־��SA_SHIRQ
 ...
 }

 /*�豸����ģ��ж�غ���*/
 void xxx_exit(void)
 {
 ...
 /*�ͷ��ж�*/
 free_irq(sh_irq, xxx_interrupt);
 ...
 }