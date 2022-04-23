from machine import LCD, Sprite, Map, Pin
import sys
import time

# Create LCD object
lcd = LCD()

# Create sprite object
ship_sprite = Sprite(lcd)
bullet_sprite = Sprite(lcd)
enemy_sprite = Sprite(lcd)
score_sprite = Sprite(lcd)

# Ship sprite dimensions
ship_size_x = 21
ship_size_y = 21
bullet_size_x = 1
bullet_size_y = 4
enemy_size_x = 16
enemy_size_y = 12

# Sprite resize factor
rf = 2

STICK_LEFT = Pin(Map.WIO_5S_LEFT, Pin.IN)
STICK_RIGHT = Pin(Map.WIO_5S_RIGHT, Pin.IN)
STICK_UP = Pin(Map.WIO_5S_UP, Pin.IN)
STICK_DOWN = Pin(61, Pin.IN)

FIRE_BUTTON = Pin(Map.WIO_KEY_C, Pin.IN)
START_BUTTON = Pin(Map.WIO_KEY_B, Pin.IN)

HALT_BUTTON = Pin(Map.WIO_KEY_A, Pin.IN)  # debugging sys.exit() button

BUZZER_PIN = Pin(Map.WIO_BUZZER, Pin.OUT)

# Ship sprite array
ar_ship_sprite = [
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 3, 1, 1, 2, 2, 2, 1, 1, 3, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 3, 1, 1, 2, 2, 2, 1, 1, 3, 1, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 3, 1, 1, 2, 4, 2, 2, 3, 2, 2, 4, 2, 1, 1, 3, 1, 0, 0,
    0, 0, 1, 3, 1, 1, 4, 2, 2, 3, 3, 3, 2, 2, 4, 1, 1, 3, 1, 0, 0,
    0, 0, 1, 2, 1, 1, 2, 2, 2, 3, 2, 3, 2, 2, 2, 1, 1, 2, 1, 0, 0,
    0, 0, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 0, 0,
    0, 0, 1, 2, 2, 2, 2, 2, 3, 2, 2, 2, 3, 2, 2, 2, 2, 2, 1, 0, 0,
    0, 0, 1, 2, 2, 2, 1, 3, 3, 2, 2, 2, 3, 3, 1, 2, 2, 2, 1, 0, 0,
    0, 0, 1, 2, 2, 1, 1, 3, 3, 1, 2, 1, 3, 3, 1, 1, 2, 2, 1, 0, 0,
    0, 0, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 0, 0,
    0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
]

ar_enemy_sprite = [
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0,
    0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0,
    0, 0, 5, 5, 5, 0, 0, 5, 5, 0, 0, 5, 5, 5, 0, 0,
    0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0,
    0, 0, 0, 0, 0, 5, 5, 0, 0, 5, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 5, 0, 5, 5, 0, 5, 5, 0, 0, 0, 0,
    0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
]

ar_bullet_sprite = [
    0,
    2,
    2,
    0,
]

delay = 0


def make_sound(tone):
    global delay
    delay += 1
    BUZZER_PIN.on()
    if (delay > tone):
        BUZZER_PIN.off()
        delay = 0


def game_over():
    lcd.setTextColor(0xF800, 0x0000)
    lcd.setTextDatum(0)
    lcd.setTextSize(4)
    lcd.drawString("GAME OVER", 50, 110)
    for snd in range(100, 400):
        for pause in range(0, 100):
            make_sound(snd)


def init_score_sprite(sprite):
    sprite.createSprite(230, 16)
    sprite.fillSprite(0x0000)
    sprite.setTextColor(0xFDA0, 0x0000)
    sprite.setTextDatum(0)
    sprite.setTextSize(2)
    sprite.drawString("Score:", 0, 0)
    sprite.setTextColor(0xF800, 0x0000)
    sprite.drawString("Enemy:", 140, 0)


def show_score(sprite, score, enemy_passed):
    sprite.setTextColor(0xFDA0, 0x0000)
    sprite.drawString(str(score), 80, 0)

    sprite.setTextColor(0xF800, 0x0000)
    if enemy_passed >= 0:
        sprite.drawString(str(3 - enemy_passed), 220, 0)
    else:
        sprite.drawString("0", 220, 0)

    sprite.pushSprite(0, 0)


def check_collision(x1, w1, y1, h1, x2, w2, y2, h2):
    bottom_collision = False

    # bottom of 1 with top of 2
    if ((x2 + w2 > x1) and (x2 < x1 + w1) and (y1 + h1 >= y2)):
        bottom_collision = True

        return bottom_collision


def rand_val(x):
    random = (time.ticks_ms() * 4393 % x)
    return random


def create_sprite(sprite, ar, size_x, size_y):
    sprite.createSprite(size_x * rf, size_y * rf)
    sprite.fillSprite(0x0000)

    l = size_x * size_y  # calculate length of array
    for y in range(0, l/size_x):
        for x in range(0, size_x):
            print(ar[x + (y*size_x)], end='')
            if x == (size_x - 1):
                print("")

            index = x + (y*size_x)
            if ar[index] == 0:
                color = 0x0000  # black
            if ar[index] == 1:
                color = 0x0000  # black
            if ar[index] == 2:
                color = 0xFFFF  # white
            if ar[index] == 3:
                color = 0xF800  # red
            if ar[index] == 4:
                color = 0x001F  # blue
            if ar[index] == 5:
                color = 0x07E0  # green
            if ar[index] == 6:
                color = 0x7BEF  # dark grey

            sprite.fillRect(x * rf, y * rf, rf, rf, color)


def game_loop():

    init_on_start = True

    while True:

        if init_on_start:

            lcd.fillScreen(lcd.color.BLACK)
            create_sprite(ship_sprite, ar_ship_sprite,
                          ship_size_x, ship_size_y)
            create_sprite(bullet_sprite, ar_bullet_sprite,
                          bullet_size_x, bullet_size_y)
            create_sprite(enemy_sprite, ar_enemy_sprite,
                          enemy_size_x, enemy_size_y)

            init_score_sprite(score_sprite)

            ship_x = 150
            ship_y = 180
            bullet_x = ship_x + int(ship_size_x * rf / 2)
            bullet_y = ship_y - (rf * 3)

            enemy_x = rand_val(320 - enemy_size_x * rf)
            enemy_y = - enemy_size_y * rf

            firing = False
            score = 0
            enemy_passed = 0
            enemy_speed = 3
            step_skip = 0

            ship_movement = True
            bullet_movement = True
            enemy_movement = True

            collision_ship_with_enemy = False
            collision_enemy_with_bullet = False

            button_b_released = False
            button_c_released = True

            init_on_start = False

        # Check for input
        if ship_movement:
            if STICK_LEFT.value() == 0:
                ship_x -= 1
            if STICK_RIGHT.value() == 0:
                ship_x += 1
            if STICK_UP.value() == 0:
                ship_y -= 1
            if STICK_DOWN.value() == 0:
                ship_y += 1

            if ship_x >= 320 - ship_size_x * rf + 2 * rf:
                ship_x = 320 - ship_size_x * rf + 2 * rf
            if ship_y >= 240 - ship_size_y * rf + 2 * rf:
                ship_y = 240 - ship_size_y * rf + 2 * rf
            if ship_x <= -(2 * rf):
                ship_x = -(2 * rf)
            if ship_y <= -(2 * rf):
                ship_y = -(2 * rf)

            # Display ship sprite on screen
            ship_sprite.pushSprite(ship_x, ship_y)

        if enemy_movement:
            enemy_sprite.pushSprite(enemy_x, enemy_y)

            if step_skip > enemy_speed:
                enemy_y += 1
                step_skip = 0

            step_skip += 1

        if enemy_y > 240:
            enemy_y = - enemy_size_y * rf
            enemy_x = rand_val(320 - enemy_size_x * rf)
            enemy_passed += 1
            for snd in range(100, 200):
                for pause in range(0, 50):
                    make_sound(snd)

        if HALT_BUTTON.value() == 0:
            sys.exit()

        if FIRE_BUTTON.value() == 0 and not firing and button_c_released:
            firing = True
            bullet_x = ship_x + int(ship_size_x * rf / 2)
            bullet_y = ship_y - (rf * 3)
            button_c_released = False

        if START_BUTTON.value() == 0 and button_b_released:
            init_on_start = True
            button_b_released = False

        if START_BUTTON.value() == 1:
            button_b_released = True

        if FIRE_BUTTON.value() == 1:
            button_c_released = True

        if firing:
            bullet_sprite.pushSprite(bullet_x, bullet_y)
            if bullet_movement:
                bullet_y -= rf
                if (bullet_y > ship_y - ship_size_y * rf):
                    make_sound(1)

            if bullet_y < -(rf * 4):
                firing = False

        # Check for collison of ship with enemy
        if check_collision(enemy_x, enemy_size_x * rf, enemy_y, enemy_size_y * rf,
                           ship_x, ship_size_x * rf, ship_y, ship_size_y * rf):
            collision_ship_with_enemy = True

        # Check for collision of enemy with bullet
        if check_collision(enemy_x, enemy_size_x * rf, enemy_y, enemy_size_y * rf,
                           bullet_x, bullet_size_x * rf, bullet_y, bullet_size_y * rf) and firing:
            collision_enemy_with_bullet = True

        if collision_ship_with_enemy or enemy_passed == 3:
            enemy_movement = False
            ship_movement = False
            bullet_movement = False

            collision_ship_with_enemy = False

            # Destroy enemy
            enemy_sprite.fillSprite(0x0000)

            # Destroy ship
            ship_sprite.fillSprite(0x0000)

            # Destroy bullet
            bullet_sprite.fillSprite(0x0000)

            enemy_y -= 5  # prevents to retrigger the collision
            enemy_passed = -1  # prevent to retrigger when enemy passed = 3

            game_over()

            ship_sprite.pushSprite(ship_x, ship_y)
            enemy_sprite.pushSprite(enemy_x, enemy_y)
            ship_sprite.pushSprite(bullet_x, bullet_y)

        if collision_enemy_with_bullet:
            # Destroy enemy
            enemy_sprite.fillSprite(0x0000)
            enemy_sprite.pushSprite(enemy_x, enemy_y)

            # Destroy bullet
            bullet_sprite.fillSprite(0x0000)
            bullet_sprite.pushSprite(bullet_x, bullet_y)

            enemy_x = rand_val(320 - enemy_size_x * rf)
            enemy_y = - enemy_size_y * rf
            bullet_x = ship_x + int(ship_size_x * rf / 2)
            bullet_y = ship_y - (rf * 3)
            firing = False

            for snd in range(50, 100):
                for pause in range(0, 100):
                    make_sound(snd)

            # Recreate enemy sprite
            enemy_sprite.deleteSprite()
            create_sprite(enemy_sprite, ar_enemy_sprite,
                          enemy_size_x, enemy_size_y)

            # Recreate bullet sprite
            bullet_sprite.deleteSprite()
            create_sprite(bullet_sprite, ar_bullet_sprite,
                          bullet_size_x, bullet_size_y)

            collision_enemy_with_bullet = False

            score += 1
            # Increase speed of enemy at every 5 score points
            if score % 5 == 0 and enemy_speed > 0:
                enemy_speed -= 1

        show_score(score_sprite, score, enemy_passed)


game_loop()
