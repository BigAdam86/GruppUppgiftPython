from abc import ABC, abstractmethod

import math

from point import Point

class Shape(ABC):
    def __init__( self, x=0, y=0, rotation=0 ):
        self.position = Point(x,y)
        self.rotation = rotation
        self.pull = Point(0,0)
        self.angular_velocity = 0.0

    @abstractmethod
    def draw(self, screen):
        pass

    def update(self, width, height, dt):
        """
        Update the position and orientation of the shape
        :param width: screen width to confine the shape to
        :param height: screen height to confine the shape to
        :return: 
        """
        # Update the position and orientation of the shape
        #  position is modified by "pull" - how much it should move each frame
        #  rotation is modified by "angular_velocity" - how much it should rotate each frame
        self.position.y += self.pull.y * dt             #position needed to be split to multiply it with deltatime
        self.position.x += self.pull.x * dt
        self.rotation += self.angular_velocity * dt
        # Use modulus to ensure that the object never vanishes from the screen
        #  Position is wrapped to always be between  (0,0)  and  (width,height)
        #  Rotation is wrapped to always be between 0 and 360 degrees
        self.position.x %= width
        self.position.y %= height
        self.rotation %= 360


    def accelerate(self, acceleration):
        """
        Cause the object to start moving by giving it a little push
        :param acceleration: ammount to accelerate the shape by,  if 0 then the shape is slowed down instead
        """
        #
        if acceleration==0:
            self.pull.x *=0.9
            self.pull.y *=0.9
        else:
            self.pull.x += (acceleration * math.cos(math.radians(self.rotation))) * 0.2         #modified acceleration value due to change to deltatime
            self.pull.y += (acceleration * math.sin(math.radians(self.rotation))) * 0.2

    def rotate(self, degrees):
        """
        Rotation the shape by a specific amount
        :param degrees: angle in degrees for the shape to be rotated by
        """
        self.rotation = ( self.rotation + degrees ) % 360;

    @abstractmethod
    def contains(self, point):
        """
        Abstract base class to perform collission detection - should return true if a point is inside
        the shape
        :param point: Point to test for collission
        :return: True or False
        """
        return False

    def jumpDrive(self):
        #jump forwards 1/4 of the screen
        self.jumpProtection = True              #Protects the user while jumping to pass through asteroids
        Amplitude = 150                         #Length of the jump
        xPos = (math.cos(math.radians(self.rotation))) * Amplitude      #calculates the landing position based on ship rotation
        yPos = (math.sin(math.radians(self.rotation))) * Amplitude

        self.position.x += xPos     #Applies the jump length on current location
        self.position.y += yPos

