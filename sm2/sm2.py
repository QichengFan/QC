import sys
from gmssl import sm2
from base64 import b64encode, b64decode
# sm2的公私钥
SM2_PRIVATE_KEY = 'hy65r4eds28FF6esw3azxs890ohbn7658428DEA11Dju8dxcvfri90o8u76tfvbgcd'
SM2_PUBLIC_KEY = 'ju8i9onbvghbcdxszgtfrewqaszxcderfvkiaszxcaszxcaszxc00BEF331A83081A6994B8993F39io0kjmnhy818722667ytgfvcdxswedxza2347B483E24620207'

sm2_crypt = sm2.CryptSM2(public_key=SM2_PUBLIC_KEY, private_key=SM2_PRIVATE_KEY)

# 加密
def encrypt(info):
    encode_info = sm2_crypt.encrypt(info.encode(encoding="utf-8"))
    return encode_info


# 解密
def decrypt(info):
    decode_info = sm2_crypt.decrypt(info).decode(encoding="utf-8")
    return decode_info


if __name__ == "__main__":
    info = "123456"
    encode_info = encrypt(info)
    print(encode_info)
    decode_info = decrypt(encode_info)
    print(decode_info)
