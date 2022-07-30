from gmssl import sm3, func
import random
import my_sm3
import struct

secret = str(random.random())
sthash = sm3.sm3_hash(func.bytes_to_list(bytes(secret, encoding='utf-8')))
secret_len = len(secret)
m = "140140140" 
cc_str = ""
cc = []

#拓展填充
def cci(aa):
    mlen = len(aa)
    aa.append(0x80)
    mlen += 1
    tail = mlen % 64
    range_end = 56
    if tail > range_end:
        range_end = range_end + 64
    for i in range(tail, range_end):
        aa.append(0x00)
    bit_len = (mlen - 1) * 8
    aa.extend([int(x) for x in struct.pack('>q', bit_len)])
    for j in range(int((mlen - 1) / 64) * 64 + (mlen - 1) % 64, len(aa)):
        global cc
        cc.append(aa[j])
        global cc_str
        cc_str += str(hex(aa[j]))
    return aa


#伪造hash值
def generate_guess_hash(old_hash, secret_len, m):
  
    vectors = []
    message = ""
    # 将old_hash分组，每组8个字节, 并转换为整数
    for r in range(0, len(old_hash), 8):
        vectors.append(int(old_hash[r:r + 8], 16))

    # 伪造消息
    if secret_len > 64:
        for i in range(0, int(secret_len / 64) * 64):
            message += 'a'
    for i in range(0, secret_len % 64):
        message += 'a'
    message = func.bytes_to_list(bytes(message, encoding='utf-8'))
    message = cci(message)
    message.extend(func.bytes_to_list(bytes(m, encoding='utf-8')))
    return my_sm3.sm3_hash(message, vectors)

guess_hash = generate_guess_hash(st_hash, secret_len, m)
new_aa = func.bytes_to_list(bytes(secret, encoding='utf-8'))
new_aa.extend(cc)
new_aa.extend(func.bytes_to_list(bytes(m, encoding='utf-8')))
new_aa_str = secret + cc_str + m
new_hash = sm3.sm3_hash(new_aa)
print("生成secret")
print("secret: "+secret)
print("secret length:%d" % len(secret))
print("secret hash:" + st_hash)
print("附加消息:", append_m)
print("计算构造的消息哈希值:" + guess_hash)

print("验证攻击是否成功...")
if new_hash == guess_hash:
    print("成功!")
else:
    print("失败")
