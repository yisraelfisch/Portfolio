
from flask import (Flask, request, jsonify)
from settings import db, app
from models import User
import json


class UserEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, User):
            user = {
                    'id': obj.id,
                    'name': obj.first_name,
                    'surname': obj.last_name
            }
            return user


@app.route('/user', methods=['GET'])
def get_all_users():
    """
    this function is map with /user endpoint and
    it renders all user records using GET Http method
    """
    message = {
     'status': 404,
     'message': 'Something went wrong'
    }
    try:
        users = User.query.all()
        list_of_users = list()
        for user in users:
            user_dict = {'id': user.id, 'name': user.first_name, 'surname': user.last_name}
            list_of_users.append(user_dict)

        message.update({
         'status': 200,
         'message': 'All records are fetched',
         'data': list_of_users
        })
    except:
        return jsonify(message)
    return jsonify(message)


@app.route('/user/<int:id>', methods=['GET'])
def get_specific_user(id: int):
    """
    this function is map with /user/pk endpoint and
    it renders specific user records with respect to its pk
    using GET Http method
    """
    message = {
        'status': 404,
        'message': 'user not found'
    }
    try:
        user = User.query.get_or_404(id)
    except:
        return jsonify(message)
    return json.dumps(user, cls=UserEncoder)


@app.route('/user', methods=['POST'] )
def create_user():
    """
    this function is map with /user endpoint and
    it create user records using POST Http method
    """
    message = {
        'status': 404,
        'message': 'Something went wrong'
    }
    result = request.json

    user = User(
          id=result["id"],
          first_name=result["name"],
          last_name=result["surname"]
        )
    try:
        db.session.add(user)
        db.session.commit()
        message.update({'status': 201,
                        'message': 'User created successfully!!! ',
                        'user_id': user.id})
        return jsonify(message)
    except:
        return jsonify(message)


@app.route('/user/<int:id>', methods=['PUT'])
def update_user(id):
    """
    this function is map with /user/pk endpoint and
    it update specific user records using PUT Http method
    """
    message = {
      'status': 404,
      'message': 'user not found'
    }
    try:
        request_data = request.get_json()
        new_name = request_data.get('name')
        new_surname = request_data.get('surname')

        try:
            current_user = User.query.get_or_404(id)
        except:
            return jsonify(message)

        if new_name:
            current_user.first_name = new_name
        if new_surname:
            current_user.last_name = new_surname

        db.session.commit()
        message.update({
            'status': 200,
            'message': 'User details updated successfully!!! '
        })
    except:
        pass
    return jsonify(message)


@app.route('/user/<int:id>', methods=['DELETE'])
def delete_user(id):
    """
    this function is map with /user/pk endpoint and
    it delete specific user records using DELETE Http method
    """
    message = {
      'status': 404,
      'message': 'user not found'
    }
    try:
        current_user = User.query.get_or_404(id)
        db.session.delete(current_user)
        db.session.commit()
        message.update({
          'status': 200,
          'message': 'user record delete successfully!!! '
        })
    except:
        pass
    resp = jsonify(message)
    return resp


if __name__ == "__main__":
    db.create_all()
    app.run(host="0.0.0.0", debug=True)














"""from fastapi import FastAPI
import sqlite3

app = FastAPI()


@app.get("/")
def read():
    info_file = open("InfoFile.txt", "r+")
    name = info_file.readline()
    info_file.close()
    return {"current": name}


@app.post("/new_name/{new_name}")
def create(new_name: str):
    info_file = open("InfoFile.txt", "r+")
    info_file.truncate(0)
    info_file.write(new_name)
    info_file.seek(0)
    name = info_file.readline()
    info_file.close()
    return {"my new name": name}


@app.put("/change_name/{new_name}")
def update(new_name: str):
    info_file = open("InfoFile.txt", "r+")
    info_file.truncate(0)
    info_file.write(new_name)
    info_file.seek(0)
    name = info_file.readline()
    info_file.close()
    return {"my new name": name}


@app.delete("/delete_name")
def delete():
    info_file = open("InfoFile.txt", "r+")
    info_file.truncate(0)
    info_file.write("no name exist")
    info_file.close()
    return {"name deleted"}"""
