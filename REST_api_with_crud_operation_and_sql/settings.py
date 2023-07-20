import os
import sqlite3
from flask import Flask
from flask_sqlalchemy import SQLAlchemy

# define sqlite database file path
db_dir = os.path.abspath('data.db')

# app settings
app = Flask(__name__)
app.config['SECRET_KEY'] = 'any-password'
app.config["DEBUG"] = True
# Database connecting for Linux
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///'+db_dir+'?check_same_thread=False'


db = SQLAlchemy(app)
app.app_context().push()
