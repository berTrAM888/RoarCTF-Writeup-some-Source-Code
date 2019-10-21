pragma solidity ^0.4.24;

// 把存款存入银行，一年后才可以取哦hhh。

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

