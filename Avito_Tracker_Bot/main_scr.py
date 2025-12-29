import telebot
import asyncio
from telebot import types
#bot = telebot.TeleBot("")

#========= main =========
print("Введите число выводов n:")
n = int(input())
print("Введите число выводов k:")
k = int(input())

async def fn1(n):
    for i in range(n):
        print("n")
        await asyncio.sleep(0)

async def fn2(k):
    for i in range(k):
        print("k")
        await asyncio.sleep(0)

async def main():
    fun1 = asyncio.create_task(fn1(n))
    fun2 = asyncio.create_task(fn2(k))

    #await asyncio.gather(fn1(n),fn2(k))
    await fun1
    await fun2

asyncio.run(main())
