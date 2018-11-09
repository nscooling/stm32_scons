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
        sh 'cd  c-501 && scons'
      }
    }
    stage('Static Analysis') {
      parallel {
        stage('cppcheck') {
          steps {
            sleep 1
          }
        }
        stage('OCLint') {
          steps {
            sleep 1
          }
        }
      }
    }
    stage('Metrics') {
      steps {
        sleep 1
      }
    }
    stage('UT') {
      steps {
        sleep 1
      }
    }
    stage('IT') {
      steps {
        sleep 1
      }
    }
    stage('ST-simulation') {
      steps {
        sleep 1
      }
    }
    stage('ST-hardware') {
      steps {
        sleep 1
      }
    }
  }
}