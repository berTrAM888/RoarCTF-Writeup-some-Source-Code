拿到合约后`0xffd1e29ab7ea57836ce43c1089230fb29fd5b27e`，与代码。

```
pragma solidity ^0.4.24;


contract FatherOwned {
    address public owner;
    modifier onlyOwner{ if (msg.sender != owner) revert(); _; }
    function FatherOwned() { owner = msg.sender; }
}

contract HoneyLock is StandardToken,FatherOwned {
    uint256 guessCode;
    uint256 guessValue;
    string public constant name = 'Coin';
    string public constant symbol = '0x0';
    uint public constant decimals = 3;
    uint public time = now + 1 years;
    uint public airDrop = 1 * (10 ** decimals);
    mapping(address => uint256) public timeHouse;
    mapping(address => bool) public takeRecord;
    address public owner;
    event FLAG(string b64email, string slogan);

    function HoneyLock() public {
      owner = msg.sender;
      takeRecord[owner] = true;
      balances[owner] = airDrop;
      timeHouse[owner] = time;
      Transfer(0x0, owner, airDrop);
  }

    function takeMoney() public returns(bool) {
      require(takeRecord[msg.sender] == false);
      balances[msg.sender] = airDrop;
      takeRecord[msg.sender] = true;
      timeHouse[msg.sender] = time;
      Transfer(0x0, msg.sender, airDrop);
      return true;
    }

    modifier lock() {
      require (now > timeHouse[msg.sender]);
      _;
    }

    function transfer(address _to, uint256 _value) lock public returns(bool) {
      super.transfer(_to, _value);
      Transfer(msg.sender, _to , _value);
    }


    function useCode(uint256 code) public payable {
      require ((code == guessCode) && (msg.value >= guessValue)); 
      owner = msg.sender;
    }

    function withdraw() public onlyOwner {
      require(takeRecord[msg.sender] == true);
      balances[msg.sender] == 0;
    }

    function CaptureTheFlag(string b64email) public returns(bool){
      require (takeRecord[msg.sender] == true);
      require (balances[msg.sender] == 0);
      emit FLAG(b64email, "Congratulations to capture the flag!");
    }

}
```

简单解读一下该合约，该用户若想获得flag，那么他必须满足两个条件：

```
      require (takeRecord[msg.sender] == true);
      require (balances[msg.sender] == 0);
```

第一个为记录值必须为true第二个为余额必须为0.


满足为true意味着要调用。

```
    function HoneyLock() public {
      owner = msg.sender;
      takeRecord[owner] = true;
      balances[owner] = airDrop;
      timeHouse[owner] = time;
      Transfer(0x0, owner, airDrop);
  }
```

而调用了这个合约之后用户的余额则变为1000.

所以我们如何将这1000的余额花掉？

我们在broke.sol函数中能发现转账函数：

```
    function transfer(address _to, uint256 _value) lock public returns(bool) {
      super.transfer(_to, _value);
      Transfer(msg.sender, _to , _value);
    }
```

但是该函数拥有修饰函数`lock`。

```
    modifier lock() {
      require (now > timeHouse[msg.sender]);
      _;
    }
```

而该函数使得该余额需要存储1年才能进行转账，所以该方法跳过。


第二个方法为使用`withdraw`函数：

```
    function withdraw() public onlyOwner {
      require(takeRecord[msg.sender] == true);
      balances[msg.sender] == 0;
    }
```

而该函数只能`onlyOwner`调用。

`modifier onlyOwner{ if (msg.sender != owner) revert(); _; }`。

那么这里需要改变owner的身份。

`这里是个坑点`。

```
    function useCode(uint256 code) public payable {
      require ((code == guessCode) && (msg.value >= guessValue)); 
      owner = msg.sender;
    }
```

这个函数看似能改变，当调用了之后会发现owner并不会改变。这是由于继承机制的问题。（蜜罐的精髓）


所以真正的方案是什么？


我们这是需要逆向整个合约。

[https://ethervm.io/decompile/ropsten/0xffd1e29ab7ea57836ce43c1089230fb29fd5b27e](https://ethervm.io/decompile/ropsten/0xffd1e29ab7ea57836ce43c1089230fb29fd5b27e)

既然上述的几种方法我们无法成功，那么我们需要通过逆向来查找是否有其他的函数了辅助我们进行。


其实在合约逆向后很容易能发现approve函数，而熟悉这个函数的用户都知道。ERC20中存在此类函数意味着拥有transferfrom类型的函数。

![image.png](https://upload-images.jianshu.io/upload_images/7862980-b1e03d0da55697bc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


而我们并没有看到transferfrom函数。于是我们继续查看逆向合同：

```
    function func_09D7(var arg0, var arg1, var arg2, var arg3) returns (var r0) {
        var var0 = 0x00;
        memory[0x00:0x20] = arg0 & 0xffffffffffffffffffffffffffffffffffffffff;
        memory[0x20:0x40] = 0x03;
        var temp0 = keccak256(memory[0x00:0x40]);
        memory[0x00:0x20] = msg.sender;
        memory[0x20:0x40] = temp0;
    
        if (arg2 > storage[keccak256(memory[0x00:0x40])]) { revert(memory[0x00:0x00]); }
    
        if (storage[0x02] + msg.sender != arg3) { revert(memory[0x00:0x00]); }
    
        var temp1 = arg2;
        var temp2 = arg0;
        memory[0x00:0x20] = temp2 & 0xffffffffffffffffffffffffffffffffffffffff;
        memory[0x20:0x40] = 0x00;
        var temp3 = storage[keccak256(memory[0x00:0x40])] - temp1;
        memory[0x00:0x20] = temp2 & 0xffffffffffffffffffffffffffffffffffffffff;
        memory[0x20:0x40] = 0x00;
        storage[keccak256(memory[0x00:0x40])] = temp3;
        var temp4 = arg1;
        memory[0x00:0x20] = temp4 & 0xffffffffffffffffffffffffffffffffffffffff;
        memory[0x20:0x40] = 0x00;
        var temp5 = storage[keccak256(memory[0x00:0x40])] + temp1;
        memory[0x00:0x20] = temp4 & 0xffffffffffffffffffffffffffffffffffffffff;
        memory[0x20:0x40] = 0x00;
        storage[keccak256(memory[0x00:0x40])] = temp5;
        memory[0x00:0x20] = temp2 & 0xffffffffffffffffffffffffffffffffffffffff;
        memory[0x20:0x40] = 0x03;
        var temp6 = keccak256(memory[0x00:0x40]);
        memory[0x00:0x20] = msg.sender;
        memory[0x20:0x40] = temp6;
        var temp7 = storage[keccak256(memory[0x00:0x40])] - temp1;
        memory[0x00:0x20] = temp2 & 0xffffffffffffffffffffffffffffffffffffffff;
        memory[0x20:0x40] = 0x03;
        var temp8 = keccak256(memory[0x00:0x40]);
        memory[0x00:0x20] = msg.sender;
        memory[0x20:0x40] = temp8;
        storage[keccak256(memory[0x00:0x40])] = temp7;
        return 0x01;
    }
 
```

这个函数中我们能看到需要传入四个参数，与`0xffffffffffffffffffffffffffffffffffffffff `进行相与操作意味着这是某个地址。

而`if (arg2 > storage[keccak256(memory[0x00:0x40])]) { revert(memory[0x00:0x00]); }`代表ERC20中的授权参数，我们从approve中能够看出该存储位置为0x03，此函数中的变量存储位置同样为0x03，所以为同一个参数。

即类似于：`require(_value <= allowed[_from][msg.sender]);`


而：`if (storage[0x02] + msg.sender != arg3) { revert(memory[0x00:0x00]); }`代表了0x02位置的参数+msg.sender需要 == arg3参数。

而位置0x02的参数可以通过如下方法进行查询，即为 `53231323`。


![image.png](https://upload-images.jianshu.io/upload_images/7862980-740d46a61e348859.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

所以我们需要传入 53231323+uint(msg.sender)。

之后我们尝试上述方案。

首先使用账户调用`takeMoney`。

![image.png](https://upload-images.jianshu.io/upload_images/7862980-e38c7a52c37aad16.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![image.png](https://upload-images.jianshu.io/upload_images/7862980-019009ef6a8ea9b3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


这个时候就满足`require (takeRecord[msg.sender] == true);`。

之后我们需要将钱转出。

```
contract attacker{
    HoneyLock target = HoneyLock(0xb27ad1cab9e54cd6bb34b41bacb0fb0e139208eb);

    function attack(address _from, address _to, uint256 _value) public{
        bytes4 method = 0x5ad0
ae39;
        // target.transferFrom(_from, _to, _value,53231323+uint256(this));
        target.call(method,_from,_to,_value,53231323+uint256(this));
    } 
}
```

所以我们在`0x9b9a30b7df47b9dbe0ec7d4bd52aaae4465f2ebe`账户下调用approve函数：

传入参数：`0x7083bcda08538cba3437d98ad01edfa73e2e2276,1000`
即赋予0x7083bcda08538cba3437d98ad01edfa73e2e2276代替账户转账1000的权利。

查看allowance得到：

![image.png](https://upload-images.jianshu.io/upload_images/7862980-b14a58ac219ced67.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

即授权成功。

之后我们进行转账操作。

调用attack函数：

![image.png](https://upload-images.jianshu.io/upload_images/7862980-91e7549df359b3e6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


此时我们需要调整一下合约的gas值：

![image.png](https://upload-images.jianshu.io/upload_images/7862980-75430f5cd78b16fc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/7862980-64568b8a837200e7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

尽量调整大一些，防止gas不足。之后查看：

![image.png](https://upload-images.jianshu.io/upload_images/7862980-1cc291ac4678026b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

之后调用`CaptureTheFlag`，成功！

![image.png](https://upload-images.jianshu.io/upload_images/7862980-626836ec884ec6ab.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
