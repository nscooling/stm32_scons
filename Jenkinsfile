pipeline {
  agent any
  stages {
    stage('Build') {
      parallel {
        stage('gcc-arm-5.4') {
          agent {
            docker {
              image 'feabhas/gcc-arm-scons-alpine'
            }

          }
          steps {
            sh 'cd  c-501 && scons'
          }
        }
        stage('gcc-arm-6.5') {
          steps {
            sleep 1
          }
        }
        stage('gcc-arm-7.2') {
          steps {
            sleep 1
          }
        }
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
      agent {
        docker {
          image 'feabhas/alpine-lizard'
        }

      }
      steps {
        sleep 1
        sh 'lizard'
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