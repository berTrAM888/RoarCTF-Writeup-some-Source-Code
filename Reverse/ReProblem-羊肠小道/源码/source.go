package main

import (
    "encoding/base64"
	"fmt"
	"os"
	"crypto/md5"
	"crypto/sha1"
    "encoding/hex"
)


func check(table [] int) bool{
	var i,j int
	for i = 3; i < 5 ;i ++{
		for j = 1; j < 3; j++ {
			if(table[i*4 + j] != 0){
				return false
			}
		}
	}

	return true
}
func de(enc *base64.Encoding, str string) string {
    data, err := enc.DecodeString(str)
    if err != nil {
        panic(err)
    }
    return string(data)
}

func wr(){
	fmt.Printf("sorry!\n")
	os.Exit(1)
}
func chedg(x int, y int) bool{
	if x < 0 && x > 4{
		return false
	}
	if y < 0 && y > 5{
		return false
	}
	return true
}

func checkvail(table [] int, x int, y int, val int) bool{
	if table[y * 4 + x] == -1 || table[y * 4 + x] == val{
		return true
	}else{
		return false
	}
}

func movepos(table [] int, direct int, num int){
	var tabletmp = [] int  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
	var x_a, y_a int
	if direct == 1{
		x_a = 0
		y_a = 1
	}else if direct == 2{
		x_a = 1
		y_a = 0
	}else if direct == 3{
		x_a = 0
		y_a = -1
	}else if direct == 4{
		x_a = -1
		y_a = 0
	}else{
		wr()
	}

	for j := 0; j < 5; j ++{
		for i := 0; i < 4; i ++{
			if(table[j * 4 + i] == num){
				tabletmp[(j + y_a) * 4 + i + x_a] = num
			}
		}
	}
	for j := 0; j < 5; j ++{
		for i := 0; i < 4; i ++{
			if(table[j * 4 + i] == num && tabletmp[j * 4 + i] == num){
				table[j * 4 + i] = num
			}else if(table[j * 4 + i] == -1 && tabletmp[j * 4 + i] == num){
				table[j * 4 + i] = num
			}else if(table[j * 4 + i] == num && tabletmp[j * 4 + i] == -1){
				table[j * 4 + i] = -1
			}
		}
	}
}

func move(table [] int, num int, direct int){
	len := 0

	for i:=0; i < 20; i++{
		if(table[i] == num){
			len = len + 1
		}
	}
	if len == 0 {
		wr()
	}

	var x, y, x_a, y_a int
	if direct == 1{
		x_a = 0
		y_a = 1
	}else if direct == 2{
		x_a = 1
		y_a = 0
	}else if direct == 3{
		x_a = 0
		y_a = -1
	}else if direct == 4{
		x_a = -1
		y_a = 0
	}else{
		wr()
	}

	vlen := 0 

	for y = 0; y < 5 ;y ++{
		for x = 0; x < 4; x++ {
			if(table[y*4 + x] == num && chedg(x + x_a, y + y_a) && checkvail(table, x + x_a, y + y_a, table[y * 4 + x])){
				vlen = vlen + 1
			}
		}
	}

	if vlen == len{
		movepos(table, direct, num)
	}else{
		wr()
	}
}

func checkposval(pos_data int) bool{
	pos := (pos_data & 0xf0) >> 4
	pos_val := pos_data & 0xf
	
	if(pos < 0 && pos > 9){
		return false
	}

	if(pos_val < 1 && pos_val > 8){
		return false
	}
	return true
}


func dog(bytes [] byte, table [] int){

	bytes_length := len(bytes)
	
	var pos_length int = 0
	var tmp_pos, tmp_val int = 0,0
	for i := 0;i < bytes_length ;i ++{
		if(checkposval(int(bytes[i]))){
			if(int(bytes[i]) & 0xf > 4){
				move(table, (int(bytes[i]) & 0xf0) >> 4, (int(bytes[i]) & 0xf) - 4) 
				move(table, (int(bytes[i]) & 0xf0) >> 4, (int(bytes[i]) & 0xf) - 4) 
			}else{
				move(table, (int(bytes[i]) & 0xf0) >> 4, int(bytes[i]) & 0xf) 
			}
		

			if tmp_pos == ((int(bytes[i]) & 0xf0) >> 4) && tmp_val != int(bytes[i]) & 0xf{
				pos_length = pos_length
			}else{
				pos_length ++ 
			}

			tmp_pos = (int(bytes[i]) & 0xf0) >> 4
			tmp_val = int(bytes[i]) & 0xf
		
			if(pos_length > 75){
				wr()
			}
		}else{
			wr()
		}	
	}
	
}

func ckfg(flag string) bool{
	h := md5.New()
    h.Write([]byte(flag)) 
	if("bce3d687dc850eee9c5e6748ecb3c1a0" == hex.EncodeToString(h.Sum(nil)) ){
		return true
	}else{
		return false
	}


	return true
}

func suc(flag string){
	h := sha1.New()
	h.Write([]byte(flag)) 
	fmt.Printf("roarctf{" + hex.EncodeToString(h.Sum(nil)) + "}");
	return;
}


//解密
func AESDecrypt(crypted,key []byte)[]byte{
	block,_ := aes.NewCipher(key)
	blockSize := block.BlockSize()
	blockMode := cipher.NewCBCDecrypter(block,key[:blockSize])
	origData := make([]byte,len(crypted))
	blockMode.CryptBlocks(origData,crypted)
	origData = PKCS7UnPadding(origData)
	return origData
}
​
//去补码
func PKCS7UnPadding(origData []byte)[]byte{
	length := len(origData)
	unpadding := int(origData[length-1])
	return origData[:length-unpadding]
}
//加密
func AESEncrypt(origData,key []byte)[]byte{
	//获取block块
	block,_ :=aes.NewCipher(key)
	//补码
	origData = PKCS7Padding(origData, block.BlockSize())
	//加密模式，
	blockMode := cipher.NewCBCEncrypter(block,key[:block.BlockSize()])
​
	//创建明文长度的数组
	crypted := make([]byte,len(origData))
​
	//加密明文
	blockMode.CryptBlocks(crypted,origData)
​
	return crypted
}
​
//补码
func PKCS7Padding(origData []byte,blockSize int)[]byte{
	//计算需要补几位数
	padding := blockSize-len(origData)%blockSize
	//在切片后面追加char数量的byte(char)
	padtext := bytes.Repeat([]byte{byte(padding)},padding)
​
	return append(origData,padtext...)	
}

func main() {
	var table = [] int  {
		1, 2, 3, 4,
		1, 0, 0, 4, 
		8, 0, 0, 5, 
		7, 6, 6, 5, 
		7, -1, -1, 9}
   
	var data string

	fmt.Scan(&data)

	if len(data) < 84 {
		wr()
	}
	if len (data) > 84{
		wr()
	}
	

	decodeBytes, err := base64.StdEncoding.DecodeString(data)

	if err != nil {
		wr()
	}
	
	dog(decodeBytes, table)
	
   	if(check(table) && ckfg(string(decodeBytes))){
		suc(string(decodeBytes))
   	}else{
		wr()
	}
	   	
}



