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
        stage('gcc-arm-7.2') {
          when {
            branch 'develop'
          }
          agent {
            docker {
              image 'feabhas/gcc7-arm-scons-alpine'
            }

          }
          steps {
            sh 'cd  c-501 && scons'
          }
        }
      }
    }
    stage('Static Analysis') {
      when {
        not {
          branch 'release'
        }
      }
      parallel {
        stage('OClint') {
          agent {
            docker {
              image 'feabhas/oclint-0.13'
            }

          }
          steps {
            sh 'cd c-501 && oclint src/*.c -- -c -I Drivers/ -I system/include/cmsis/ -D STM32F407xx'
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
      when {
        not {
          branch 'release'
        }
      }
      agent {
        docker {
          image 'feabhas/alpine-lizard'
        }

      }
      steps {
        sh 'lizard -C 50'
      }
    }
    stage('UnitTests') {
      when {
        not {
          branch 'release'
        }
      }
      steps {
        sleep 1
      }
    }
    stage('IntTests') {
      when {
        branch 'release'
      }
      steps {
        sleep 1
      }
    }
    stage('SysTest-sim') {
      when {
        branch 'release'
      }
      steps {
        sleep 1
      }
    }
    stage('SysTest-hw') {
      when {
        branch 'release'
      }
      steps {
        sleep 1
      }
    }
  }
}