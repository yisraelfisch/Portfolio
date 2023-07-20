from settings import db
import sqlite3
from sqlalchemy import Column, Integer, Text


class User(db.Model):

    id = db.Column(db.Integer, primary_key=True)
    first_name = db.Column(db.String(60))
    last_name = db.Column(db.String(60))

    def __str__(self):
        return f"{self.id }+ {self.first_name} + {self.last_name}"

