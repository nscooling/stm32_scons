pipeline {
  agent {
    docker {
      image 'feabhas/gcc-arm-scons-alpine'
    }

  }
  stages {
    stage('Build') {
      steps {
        sh '''cd  c-501
scons'''
      }
    }
  }
}