import socket
from tkinter import Tk, Button, Entry, Text, END, Label, DISABLED, NORMAL


def server_comunication(ip_address, port, bash_command):
    """Komunikacja z serwerem poprzez socket"""

    # utworzenie socketu, deskryptora do dostepu
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # polaczenie z serwerem
    s.connect((ip_address, socket.htons(int(port))))

    # przeslanie na serwer polecenia bash
    s.sendall(bash_command)

    # odbranie informacji z serwera o stalym rozmiarze 1024 znakow ascii
    data = s.recv(1024)

    # zamkniecie polaczenia
    s.close()

    # zwrocenie zdekodowanych danych z serwera, z zaminą na string
    return str(data, "ascii")


def click_action(button, ip_address, port, bash_command, output):
    """Akcja wywołująca połączenie z serwerem po nacisnieciu przycisku"""

    # zamiana do komunikacji z serwerem utf-8 / ascii
    tmp = bash_command.get().strip()[:32] + '\0'
    str_to_b = bytes(tmp, 'ascii')
    
    # komunikat o stalym rozmiarze 32, pytanie czu nulle na poczatku czy na koncu
    str_to_b += bytes(32 - len(str_to_b))
    #print(str_to_b, len(str_to_b), str(str_to_b, 'ascii'))

    try:
        data = server_comunication(ip_address.get().strip(), port.get().strip(), str_to_b)
    except Exception:
        data = "Blad komunikacji z serwerem"

    # prezentacja wyników
    output.config(state=NORMAL)
    output.delete('1.0', END)
    output.insert(END, "[INPUT] \n")
    output.insert(END, bash_command.get().strip()[:32])
    output.insert(END, "\n\n")
    output.insert(END, "[OUTPUT]\n")
    output.insert(END, data)
    output.insert(END, "\n\n")
    output.config(state=DISABLED)


def main():
    root = Tk()

    root.geometry("1000x900")
    root.title("Simple Telnet GUI")

    label_ip_address = Label(root, text="Adres IP serwera:")
    label_ip_address.pack()
    ip_address = Entry(root, width=70)
    ip_address.pack()

    label_port = Label(root, text="Port na serwerze:")
    label_port.pack()
    port = Entry(root, width=70)
    port.pack()

    label_bash_command = Label(root, text="Polecenie BASH:")
    label_bash_command.pack()
    bash_command = Entry(root, width=70)
    bash_command.pack()

    click_button = Button(root, text="Wyślij polecenie", width=20)
    click_button.pack()


    textbox = Text(root, width = 100, height = 45)
    textbox.config(state=DISABLED)
    textbox.pack()

    click_button.config(command=lambda: click_action(click_button, ip_address, port, bash_command, textbox))
    root.mainloop()


if __name__ == "__main__":
    main()