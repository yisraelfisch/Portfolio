pipeline {
    agent any

    triggers {
        githubPush()
    }

    stages {
        stage('Checkout Code') {
            steps {
                checkout scm
            }
        }
        
        stage('Install Dependencies') {
            steps {
                sh 'npm install -g newman'
            }
        }
        
        stage('Run Postman Tests') {
            steps {
                sh '/home/yisrael/git_hub/REST_api_with_crud_operation_and_sql/postman_collection.json'
            }
        }
    }
}


