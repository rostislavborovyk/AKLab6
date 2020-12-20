#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/ktime.h>

struct my_list_head {
struct my_list_head *next;
ktime_t time;
};


MODULE_AUTHOR("Rostyslav Borovyk IV-82");
MODULE_DESCRIPTION("Lab 6, prints hello and tracks time when it's printed");
MODULE_LICENSE("Dual BSD/GPL");

static struct my_list_head *hd;

static uint times;
 module_param(times , uint , 0444);
 MODULE_PARM_DESC(times , "The amount of times to print hello");

static int __init hello(void)
{
 uint i;

struct my_list_head *first_var, *second_var;
 pr_info("times: %d\n", times);

 if (times == 0) {
	pr_warn("times is 0");
 } else if (times >= 5 && times <= 10) {
	pr_warn("times is between 5 and 10");
 } else if (times > 10) {
	pr_err("times is greater than 10");
 return -EINVAL;
}

 hd = kmalloc(sizeof(struct my_list_head *), GFP_KERNEL);
 first_var = hd;

 for (i = 0; i < times; i++) {
	first_var->next = kmalloc(sizeof(struct my_list_head), GFP_KERNEL);
	first_var->time = ktime_get();
	pr_info("hello!");
	second_var = first_var;
	first_var = first_var->next;
}
 if (times != 0) {
	kfree(second_var->next);
	second_var->next = NULL;
}
 return 0;
}


static void __exit hello_exit(void)
{
struct my_list_head *var;

 while (hd != NULL && times != 0) {
	var = hd;
	pr_info("Time: %lld", var->time);
	hd = var->next;
	kfree(var);
}

 if (times == 0)
	pr_info("time is 0 ");

 pr_info("");
}

 module_init(hello);
 module_exit(hello_exit);

