from fastapi import FastAPI

app = FastAPI()


@app.get("/")
def read():
    info_file = open("InfoFile.txt", "r+")
    name = info_file.readline()
    info_file.close()
    return {"current": name}


@app.get("/new_name/{new_name}")
def create(new_name: str):
    info_file = open("InfoFile.txt", "r+")
    info_file.truncate(0)
    info_file.write(new_name)
    info_file.seek(0)
    name = info_file.readline()
    info_file.close()
    return {"my new name": name}


@app.get("/change_name/{new_name}")
def update(new_name: str):
    info_file = open("InfoFile.txt", "r+")
    info_file.truncate(0)
    info_file.write(new_name)
    info_file.seek(0)
    name = info_file.readline()
    info_file.close()
    return {"my new name": name}

@app.get("/delete_name")
def delete():
    info_file = open("InfoFile.txt", "r+")
    info_file.truncate(0)
    info_file.write("no name exist")
    info_file.close()
    return {"name deleted"}


   # global name
   # name = new_name
   # return {"my new name": name}