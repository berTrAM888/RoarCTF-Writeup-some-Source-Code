# zprotect

## 题目描述
It's a zprotect or 'zprotect'?

## 分值预估
500

## 难度
难

## Flag
RoarCTF{wm-0h_Th1s_i5_4_Zprotect!}

## 环境
Linux 64位ubuntu 4.13.0-36-generic

## 思路
题目主体是一个linux的驱动逆向。

判断是否存在**/home/ppprocce/ssooor**文件，不存在则退出。
```
	filename = "/home/ppprocce/ssooor";
	int read_res;
	read_res  = read_from_file(filename, file_content);
	if(read_res != 0)
	{
		if(DEV)
		{
			printk("[Cuora_init function INFO] read_from_file function ERROR");
		}
		//kill the entire process when can't read file.
		return -1;
	}
```

然后判断文件内容，文件内容应满足两个条件：
* CRC32校验通过
* 经过排序的内容应符合check

通过爆破，得到此处的字符串应为 **/tmp/RoarCTF/flag**

检测该文件是否存在，不存在则退出。

检测该文件内容：文件内容为flag

flag的检测方式为：
* 将flag与 **/tmp/RoarCTF/flag/tmp/RoarCTF/flag** 作处理，得到两组字符串。
* 将两组字符串的高地位互换进行check。

```
	for(i=0;i<strlen(flag);i++)
	{
		res_part1[i] = (flag[i] ^ 0x55) + (temp_file_content[i] ^ 0xAA);
		res_part2[i] = (flag[i] ^ 0xAA) + (temp_file_content[i] ^ 0x55);
		res_part1[i] = (res_part1[i] / 4) | (res_part2[i] * 64);
		res_part2[i] = (res_part2[i] * 4) | (res_part2[i] / 64);
		//printk("res_part1[0x%x] is: 0x%x\n", i, res_part1[i]);
		//printk("res_part2[0x%x] is: 0x%x\n", i, res_part2[i]);
	}
```

## 测试思路
创建 **/home/ppprocce/ssooor** 文件，其中写入 **/tmp/RoarCTF/flag**。

创建**/tmp/RoarCTF/flag** 文件，其中写入 **RoarCTF{wm-0h_Th1s_i5_4_Zprotect!}**。

加载驱动，等待初始化结束后，卸载驱动。（校验过程在卸载中。）


