import serial.tools.list_ports

from tkinter import *
from tkinter import ttk

from time import sleep

ONE_NUM_ELEMENT_ID = 0
ONE_STATUS_ELEMENT_ID = 1
END_ID = 0xff

root = Tk()

root.resizable(True, True)


def read_config(config):
    global ONE_NUM_ELEMENT_ID, ONE_STATUS_ELEMENT_ID, END_ID

    config_file = open(config, "r")
    conf = []
    while line := config_file.readline():
        splitted_line = line.split()
        if splitted_line[0] == str(ONE_NUM_ELEMENT_ID):
            conf.append({"type": splitted_line[0],
                         "id": splitted_line[1],
                         "name": splitted_line[2],
                         "size": splitted_line[3],
                         "num_x": [splitted_line[i] for i in range(4, 4 + int(splitted_line[3]))],
                         "num_y": [splitted_line[i] for i in range(4 + int(splitted_line[3]), 4 + int(splitted_line[3]) + int(splitted_line[3]))]})
        else:
            conf.append({"type": splitted_line[0],
                         "id": splitted_line[1],
                         "name": splitted_line[2],
                         "num_x": splitted_line[3],
                         "num_y": splitted_line[4]})
    return conf


def write_config(conf, port):
    global ONE_NUM_ELEMENT_ID, ONE_STATUS_ELEMENT_ID, END_ID

    for line in conf:
        port.write(bytes([int(line['type'])]))
        sleep(0.1)
        port.write(bytes([int(line['id'])]))
        sleep(0.1)
        if int(line['type']) == ONE_NUM_ELEMENT_ID:
            port.write(bytes([int(line['size'])]))
            sleep(0.1)
            for i in range(int(line['size'])):
                port.write(bytes([int(line['num_x'][i])]))
                sleep(0.1)
                port.write(bytes([int(line['num_y'][i])]))
                sleep(0.1)

        if int(line['type']) == ONE_STATUS_ELEMENT_ID:
            port.write(bytes([int(line['num_x'])]))
            sleep(0.1)
            port.write(bytes([int(line['num_y'])]))
            sleep(0.1)

    port.write(bytes([END_ID]))
    sleep(0.1)

def connect_port(config, port):
    conf = read_config(config.strip())

    ser = serial.Serial(port, baudrate=38400)
    write_config(conf, ser)

    label = Label(text="Параметры:")
    label.pack()

    lables = [Label() for x in range(len(conf))]
    for lab in lables:
        lab.pack()

    def shedule_function():
        if ser.inWaiting():
            id = ser.read(1)
            data = ser.read(1)
            print(id, data)
            for lab in range(len(lables)):
                if bytes([int(conf[lab]['id'])]) == id:
                    if int(conf[lab]['type']) == ONE_STATUS_ELEMENT_ID:
                        lables[lab].config(text=f"{conf[lab]['name'].replace('_', ' ')}: "
                                                f"{'да' if int.from_bytes(data, byteorder='little') else 'нет'}")
                    else:
                        lables[lab].config(text=f"{conf[lab]['name'].replace('_', ' ')}: "
                                                f"{int.from_bytes(data, byteorder='little')}")

        root.after(10, shedule_function)

    shedule_function()
    root.mainloop()


def generate_select():
    ports = serial.tools.list_ports.comports()

    ports_str = list(map(lambda x: x.device, ports))

    label = Label(text="Выберите устройство:")
    label.pack()

    box = ttk.Combobox(values=ports_str)
    box.pack(anchor=NW, padx=6, pady=6)

    label2 = Label(text="Выберите фаил конфигурации:")
    label2.pack()

    filename = Text(height=1, wrap="char")
    filename.pack()

    button = 0

    def button():
        port = box.get()
        fl = filename.get("1.0", "end")
        print(port, fl)
        label.destroy()
        box.destroy()
        label2.destroy()
        filename.destroy()
        button.destroy()
        connect_port(fl, port)


    button = Button(text="Старт", command=button)
    button.pack()

    root.mainloop()

generate_select()

