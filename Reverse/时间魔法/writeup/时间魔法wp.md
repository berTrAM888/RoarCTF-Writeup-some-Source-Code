# 时间魔法

识别文件发现是android backup，通过abe.jar提取出base.apk和db.db

逆向java层可知每秒执行一次字段增加操作

直接提取db不可，native层存在加密

passwd跟时间有关，根据题目说明算出时间戳为`-1368859078`，对System.currentTimeMillis的返回值进行Hook，这里需要设置仅触发一次，因为计时器内部会使用到该函数，产生影响



另一方面需要选取合适的注入点，拿到`DatabaseHelper`中的`db`成员，并对其调用`rawQuery`方法执行`select`语句

通过`select sql from sqlite_master`可知flag存放在db表中，`select flag from db`即可获得flag



frida hook：

```javascript
var expr = "select flag from db";
var flag = 0;
Java.perform(function(){
    var ma = Java.use("ctf.wm.timedatabase.DatabaseHelper");
    ma.plus.implementation = function()
    {
        var dbClass = Java.use("net.sqlcipher.database.SQLiteDatabase");
        var db = Java.cast(ma.db.value, dbClass);
        var c = db.rawQuery(expr, null);
        var cursorClass = Java.use("android.database.Cursor");
        var cursor = Java.cast(c, cursorClass);
        while(cursor.moveToNext())
        {
            console.log(cursor.getString(0));
        }
    }

    var system = Java.use("java.lang.System");
    system.currentTimeMillis.implementation = function()
    {
        if(flag==0){
        console.log("time hook success!");
        flag = 1;
        return -1368859078000;
        }
        return this.currentTimeMillis();
    }
});
```

