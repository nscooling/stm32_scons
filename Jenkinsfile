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
        sh '''ls
cd  c-501
pwd
ls
echo $PATH
ls /home/dev'''
      }
    }
  }
}