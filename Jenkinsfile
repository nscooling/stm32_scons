pipeline {
  agent {
    docker {
      image 'feabhas/gcc7-arm-scons-alpine'
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