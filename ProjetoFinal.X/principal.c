#include "conf.h" 
#include "i2c.h"
#include "lcd.h"
#include "rtc.h" 
#include "teclado.h"

unsigned int est = 0, cond = 0;
int escolha();
void trocarSenha();

void main(void) {

    TRISA = 0x10;
    TRISB = 0x0F;
    TRISD = 0x00; // Portas D e E sao usadas no LCD
    TRISE = 0x00;
    TRISC = 0x01;
    ADCON1 = 0x0F;
    TRISCbits.TRISC0 = 0;
    TRISEbits.TRISE0 = 0;


    unsigned int temp = 5, opc;

    lcd_init();
    i2c_init();
    lcd_cmd(0x0C);
    lcd_cmd(L_CLR);


    while (1) {
        if (est == 0) {
            lcd_cmd(L_CLR);
            TRISB = 0x0F;
            TRISD = 0x00;
            
            if (PORTEbits.RE0 == 1) {
                cond = 0;
                temp = 5;
            } 
            if (PORTCbits.RC0 == 1) {
                cond = 2;
                temp = 5;
            }
            
            while (1) {
                if (PORTBbits.RB0 == 0 && PORTCbits.RC0 == 1 || PORTBbits.RB0 == 0 && PORTEbits.RE0 == 1) {
                    TRISB = 0x00;
                    PORTBbits.RB0 = 1;
                    est = escolha();
                    if (est == 1) {
                        break;
                    } else {
                        if (PORTEbits.RE0 == 1) {
                            cond = 0;
                            temp = 5;
                        } else if (PORTCbits.RC0 == 1) {
                            cond = 2;
                            temp = 5;
                        }
                    }
                }
                TRISB = 0x0F;
                TRISD = 0x00;
                if (PORTBbits.RB2 == 0 && PORTCbits.RC0 == 1 || PORTBbits.RB2 == 0 && PORTEbits.RE0 == 1) {
                    TRISB = 0x00;
                    PORTBbits.RB2 = 1;
                    trocarSenha();
                    if (PORTEbits.RE0 == 1) {
                        cond = 0;
                        temp = 5;
                    } else if (PORTCbits.RC0 == 1) {
                        
                        cond = 2;
                        temp = 5;
                    }
                }

                TRISB = 0x0F;
                TRISD = 0x00;
                lcd_cmd(L_L1);
                lcd_str("Estado: Auto    ");
                lcd_str("");
                rtc_r();
                lcd_cmd(L_L2);
                lcd_str("Hora: ");
                lcd_str((const char *) time);
                lcd_str(" ");
                lcd_cmd(L_L4);
                lcd_str("Janela: ");

                if (time[1] == '6' && time[3] == '0' && time[4] == '0' && cond == 1) {
                    lcd_cmd(L_L4 + 8);
                    lcd_str("Abrindo");
                    PORTEbits.RE0 = 0;
                    opc = 1;
                    cond++;
                }
                if (temp == 5 && cond == 2) {
                    lcd_cmd(L_L4 + 8);
                    lcd_str("Aberta ");
                    PORTCbits.RC0 = 1;
                    opc = 0;
                    temp = 0;
                    cond++;
                }
                if (time[0] == '1' && time[1] == '8' && time[3] == '0' && time[4] && cond == 3) {
                    lcd_cmd(L_L4 + 8);
                    lcd_str("Fechando");
                    PORTCbits.RC0 = 0;
                    opc = 1;
                    cond = 0;
                }
                if (cond == 0 && temp == 5) {
                    lcd_cmd(L_L4 + 8);
                    lcd_str("Fechado ");
                    PORTEbits.RE0 = 1;
                    cond++;
                    opc = 0;
                    temp = 0;
                }

                if (opc == 1) {
                    temp++;
                }

            }
        } else if (est == 1) {
            lcd_cmd(L_CLR);
            TRISB = 0x0F;
            TRISD = 0x00;
            if (PORTEbits.RE0 == 1) {
                cond = 0;
                temp = 5;
            } else if (PORTCbits.RC0 == 1) {
                cond = 2;
                temp = 5;
            }
            while (1) {
                if (PORTBbits.RB0 == 0 && PORTCbits.RC0 == 1 || PORTBbits.RB0 == 0 && PORTEbits.RE0 == 1) {
                    TRISB = 0x00;
                    PORTBbits.RB0 = 1;
                    est = escolha();
                    if (est == 0) {
                        break;
                    } else {
                        if (PORTEbits.RE0 == 1) {
                            cond = 0;
                            temp = 5;
                        } else if (PORTCbits.RC0 == 1) {
                            cond = 2;
                            temp = 5;
                        }
                    }
                }
                if (PORTBbits.RB2 == 0 && PORTCbits.RC0 == 1 || PORTBbits.RB2 == 0 && PORTEbits.RE0 == 1) {
                    TRISB = 0x00;
                    PORTBbits.RB2 = 1;
                    trocarSenha();
                    if (PORTEbits.RE0 == 1) {
                        cond = 0;
                        temp = 5;
                    } else if (PORTCbits.RC0 == 1) {
                        cond = 2;
                        temp = 5;
                    }
                }
                TRISB = 0x0F;
                lcd_cmd(L_L1);
                lcd_str("Estado: Manual  ");
                rtc_r();
                lcd_cmd(L_L2);
                lcd_str("Hora: ");
                lcd_str((const char *) time);
                lcd_str(" ");
                lcd_cmd(L_L4);
                lcd_str("Janela: ");

                if (PORTBbits.RB1 == 0 && cond == 1) {
                    lcd_cmd(L_L4 + 8);
                    lcd_str("Abrindo");
                    PORTEbits.RE0 = 0;
                    opc = 1;
                    cond++;
                }
                if (temp == 5 && cond == 2) {
                    lcd_cmd(L_L4 + 8);
                    lcd_str("Aberta ");
                    PORTCbits.RC0 =1;
                    cond++;
                    opc = 0;
                    temp = 0;
                }
                if (PORTBbits.RB1 == 0 && cond == 3) {
                    lcd_cmd(L_L4 + 8);
                    lcd_str("Fechando");
                    PORTCbits.RC0 = 0;
                    opc = 1;
                    cond = 0;
                }
                if (temp == 5 && cond == 0) {
                    lcd_cmd(L_L4 + 8);
                    lcd_str("Fechado ");
                    PORTEbits.RE0 =1;
                    cond++;
                    opc = 0;
                    temp = 0;
                }

                if (opc == 1) {
                    temp++;
                }

            }
        }
    }

}

int escolha() {

    unsigned char tmp;
    unsigned char i, cont = 0;
    unsigned char senha[5];

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Digite a senha:");
    for (i = 0; i < 5; i++) {
        TRISB = 0xF0;
        TRISD = 0x0F;
        tmp = tc_tecla();
        while (tmp == 255) {
            tmp = tc_tecla();
        }
        TRISD = 0x00;
        if (tmp == 10) {
            tmp = tmp + 0x20;
        } else {
            if (tmp == 12) {
                tmp = tmp + 0x17;
            } else {
                tmp = tmp + 0x30;
            }
        }
        lcd_cmd(L_L2 + i);
        lcd_dat(tmp);
        __delay_ms(100);
        lcd_cmd(L_L2 + i);
        lcd_str("*");
        senha[i] = tmp;
        if (senha[i] == e2pext_r(i)) {
            cont++;
        }
    }

    if (cont == 5) {
        lcd_cmd(L_CLR);
        lcd_cmd(L_L1);
        lcd_str(" Senha correta ");
        lcd_str("");
        __delay_ms(50);
        if (est == 0) {
            est = 1;
        } else est = 0;

    } else {
        lcd_cmd(L_CLR);
        lcd_cmd(L_L1);
        lcd_str(" Senha incorreta ");
        lcd_str("");
        __delay_ms(50);
    }
    return est;
}

void trocarSenha() {

    unsigned char tmp;
    unsigned char i, cont = 0;
    unsigned char senha[5];

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Digite senha");
    lcd_cmd(L_L2);
    lcd_str("antiga:");
    for (i = 0; i < 5; i++) {
        TRISB = 0xF0;
        TRISD = 0x0F;
        tmp = tc_tecla();
        while (tmp == 255) {
            tmp = tc_tecla();
        }
        TRISD = 0x00;
        if (tmp == 10) {
            tmp = tmp + 0x20;
        } else {
            if (tmp == 12) {
                tmp = tmp + 0x17;
            } else {
                tmp = tmp + 0x30;
            }
        }
        lcd_cmd(L_L3 + i);
        lcd_dat(tmp);
        __delay_ms(100);
        lcd_cmd(L_L3 + i);
        lcd_str("*");
        senha[i] = tmp;
        if (senha[i] == e2pext_r(i)) {
            cont++;
        }
    }

    if (cont == 5) {
        lcd_cmd(L_CLR);
        lcd_cmd(L_L1);
        lcd_str("Digite senha");
        lcd_cmd(L_L2);
        lcd_str("nova:");
        for (i = 0; i < 5; i++) {
            TRISB = 0xF0;
            TRISD = 0x0F;
            tmp = tc_tecla();
            while (tmp == 255) {
                tmp = tc_tecla();
            }
            TRISD = 0x00;
            if (tmp == 10) {
                tmp = tmp + 0x20;
            } else {
                if (tmp == 12) {
                    tmp = tmp + 0x17;
                } else {
                    tmp = tmp + 0x30;
                }
            }
            lcd_cmd(L_L3 + i);
            lcd_dat(tmp);
            __delay_ms(100);
            lcd_cmd(L_L3 + i);
            lcd_str("*");
            e2pext_w(i, tmp);
        }
        lcd_cmd(L_CLR);
    } else {
        lcd_cmd(L_CLR);
        lcd_cmd(L_L1);
        lcd_str(" Senha incorreta ");
        __delay_ms(50);
        lcd_cmd(L_CLR);
    }

}