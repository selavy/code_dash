#!/usr/bin/env python3

import sys

class Ship():
    def __init__(self, type, health, dmg):
        self._type = type
        self._health = health
        self._dmg = dmg
        self._alive = True
    def fight(self, ship):
        pass
    def check(self):
        if self._health <= 0:
            self._alive = True
    def __str__(self):
        return self._type

class Dreadnaught(Ship):
    def __init__(self):
        super(Dreadnaught, self).__init__("DN", 750000, 10000)
    def fight(self, ship):
        if ship._type == 'B' or ship._type == 'F':
            ship._health -= 0.1 * self._dmg
        else:
            ship._health -= self._dmg

class Cruiser(Ship):
    def __init__(self):
        super(Cruiser, self).__init__("CR", 500000, 5000)
    def fight(self, ship):
        if ship._type == 'B' or ship._type == 'F':
            ship._health -= 0.2 * self._dmg
        else:
            ship._health -= self._dmg

class Destroyer(Ship):
    def __init__(self):
        super(Destroyer, self).__init__("DE", 250000, 2500)
    def fight(self, ship):
        ship._health -= self._dmg

class PatrolVessel(Ship):
    def __init__(self):
        super(PatrolVessel, self).__init__("PV", 75000, 1000)
    def fight(self, ship):
        if ship._type == 'F' or ship._type == 'B':
            ship._alive = False
        else:
            ship._health -= self._dmg

class Fighter(Ship):
    def __init__(self):
        super(Fighter, self).__init__("F", 2500, 200)
    def fight(self, ship):
        if ship._type == 'B':
            ship._alive = False
        else:
            ship._health -= ship._dmg

class Bomber(Ship):
    def __init__(self):
        super(Bomber, self).__init__("B", 2500, 200)
    def fight(self, ship):
        if ship._type == "CR" or ship._type == "DE":
            ship._health -= 500 * self._dmg
        elif ship._type == "DN":
            ship._health -= 1000 * self._dmg
        else:
            ship._health -= self._dmg

def convert(ll):
    z = []
    for l in ll:
        if l == "DN":
            z.append(Dreadnaught())
        elif l == "CR":
            z.append(Cruiser())
        elif l == "DE":
            z.append(Destroyer())
        elif l == "PV":
            z.append(PatrolVessel())
        elif l == "F":
            z.append(Fighter())
        elif l == "B":
            z.append(Bomber())
    return z

def checkList(ships):
    return [ship for ship in ships if ship._alive]
    
def fight(enemy, friend):
    e = convert(enemy)
    f = convert(friend)
    while len(e) > 0 and len(f) > 0:
#        print('Fighting', e[0], 'hlth:', e[0]._health, 'vs', f[0], 'hlth:', f[0]._health)
        e[0].fight(f[0])
        f[0].fight(e[0])
        if e[0]._health <= 0:
            e[0]._alive = False
        if f[0]._health <= 0:
            f[0]._alive = False
        if not e[0]._alive:
            e = e[1:]
        if not f[0]._alive:
            f = f[1:]
#    print('len(f)',len(f),'len(e)',len(e))
    if len(f):
        print('VICTORY IS ASSURED')
    else:
        print('RETREAT')



def chomp(line):
    return line[:-1]

if __name__ == '__main__':
    enemy = []
    friend = []
    e = False
    for line in sys.stdin:
        line = chomp(line)
        if "BEGIN BATTLE" in line:
            enemy = []
            friend = []
        elif "END BATTLE" in line:
#            print('END BATTLE')
            fight(enemy, friend)
        elif "ENEMY" in line:
            e = True
        elif "FRIENDLY" in line:
            e = False
        elif e:
            enemy = line.split(',')
        else:
            friend = line.split(',')

            
