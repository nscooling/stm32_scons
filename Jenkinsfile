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
        stage('OClint') {
          agent {
            docker {
              image 'feabhas/oclint-0.13'
            }

          }
          steps {
            sh 'cd c-501 && oclint */*.c -- -c -I Drivers/'
          }
        }
        stage('cppcheck') {
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
        sh 'lizard -C 50'
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