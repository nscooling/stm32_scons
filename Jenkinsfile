pipeline {
  agent any
  stages {
    stage('Build') {
      agent {
        docker {
          image 'feabhas/gcc-arm-scons-alpine'
        }

      }
      steps {
        sh '''cd  c-501
pwd
ls
echo $PATH'''
      }
    }
  }
}