import telebot
import asyncio
from telebot import types
bot = telebot.TeleBot("8286579752:AAFBUEPL2CSydmxMrW2kVfpIUZv2BLoS8vw")

#========= bot =========

@bot.message_handler(commands=["start"])

def start(message):
    markup = types.ReplyKeyboardMarkup(resize_keyboard = True)
    btn1 = types.KeyboardButton("Добавить объявление")
    btn2 = types.KeyboardButton("Убрать объявление")
    btn3 = types.KeyboardButton("Список всех объявления")
    markup.add(btn1,btn2)
    bot.send_message(message.from_user.id, "Йоооу", reply_markup = markup)


bot.polling(none_stop=True, interval=0)


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
