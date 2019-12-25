def compilerImageTitle = "dreamkas-rf-compiler"
def libraryImageTitle = "dreamkas-sf-library"
def cashboxIP = "192.168.242.180"
def fisgoVersion
def usedTags
def patchMd5
def fiscatMd5compiled
def fiscatMd5dirPatch

pipeline{
    agent any
    options {
        checkoutToSubdirectory("FisGo")
    }
    stages{
        stage("Build Libraries"){
            steps{
                
                script{
                    if(env.GIT_BRANCH.equals("master")) {
                        fisgoVersion = getFisgoVersionFromConfig()
                        usedTags = getTags()
                        println(fisgoVersion)
                        println(usedTags)

                        if(usedTags.contains(fisgoVersion)) {
                            currentBuild.result = 'ABORTED'
                            error('Tags already contain current fisgo build version')
                        }
                    }
                }

                echo "Cloning FisGo_CI repository code..."
                cloneCiRepo()
                
                informGitOnStageStart()
                
                echo "Creating compiler image..."
                
                echo "Building libraries inside docker image..."
                
                echo "Copying libraries into workspace..."
            }
            post{
                success{
                    informGitOnStageSuccess()
                }
                failure{
                    informGitOnStageFailure()
                }
            }
        }

        stage("Compile Fiscat"){
            steps{
                informGitOnStageStart()
            }
            post{
                success{
                    informGitOnStageSuccess()
                }
                failure{
                    informGitOnStageFailure()
                }
            }
        }

        stage("Compile Unit Tests"){
            steps{
                informGitOnStageStart()
            }
            post{
                success{
                    informGitOnStageSuccess()
                }
                failure{
                    informGitOnStageFailure()
                }
            }
        }

        stage("Patch Device"){
            steps{
                informGitOnStageStart()
            }
            post{
                success{
                    informGitOnStageSuccess()
                }
                failure{
                    informGitOnStageFailure()
                }
            }
        }

        stage("Run Unit Tests"){
            steps{
                informGitOnStageStart()
            }
            post{
                success{
                    informGitOnStageSuccess()
                }
                failure{
                    informGitOnStageFailure()
                }
            }
        }

        stage("Run System Tests"){
            steps{
                informGitOnStageStart()
            }
            post{
                success{
                    informGitOnStageSuccess()
                }
                failure{
                    informGitOnStageFailure()
                }
            }
        }

        stage("Deploy Patch"){
            when {
                branch 'master'
            }
            steps{
                informGitOnStageStart()

                echo "Deploying patch..."
                
                sh "rm -rf dirPatch"
                dir("dirPatch") {
                    git credentialsId: "fisgo-ci-github", url: "https://github.com/egorsego/dirPatch.git", branch: "master"
                }

                sh "cd ${env.WORKSPACE}/dirPatch/ ; touch file_${fisgoVersion}.txt"
                
                //TODO: upload tar to prod server
                
                withCredentials([usernamePassword(credentialsId: 'fisgo-ci-github', usernameVariable: 'USER', passwordVariable: 'PASS')]) {
                    sh """
                        cd dirPatch
                        git remote set-url origin https://${USER}:${PASS}@github.com/dreamkas/dirPatch.git
                        git branch

                        cd ../FisGo 
                        git config --local credential.helper "!f() { echo username=\\$USER; echo password=\\$PASS; }; f"
                        git branch
                    """
                }
            }
            post{
                success{
                    informGitOnStageSuccess()
                }
                failure{
                    informGitOnStageFailure()
                }
            }
        }
    }
    post{
        always{
             removeUnusedContainersAndDanglingImages()
        }
    }
}

void removeUnusedContainersAndDanglingImages() {
    echo "Removing dangling images..." 
    sh "docker container prune --force"
    sh "docker image prune --filter 'dangling=true' --force"
}

void informGitOnStageStart() {
    withCredentials([string(credentialsId: 'pr_builder_plugin', variable: 'TOKEN')]) {  
        sh "${env.WORKSPACE}/CI/bash_scripts/stage_start.sh $TOKEN '${env.STAGE_NAME}'"
    }
}

void informGitOnStageSuccess() {
    withCredentials([string(credentialsId: 'pr_builder_plugin', variable: 'TOKEN')]) {
	    sh "${env.WORKSPACE}/CI/bash_scripts/stage_success.sh $TOKEN '${env.STAGE_NAME}'"
    }
}

void informGitOnStageFailure() {
    withCredentials([string(credentialsId: 'pr_builder_plugin', variable: 'TOKEN')]) {
	    sh "${env.WORKSPACE}/CI/bash_scripts/stage_failure.sh $TOKEN '${env.STAGE_NAME}'"
    }
}

void cloneCiRepo() {
    sh "rm -rf CI"
    dir("CI") {
        git credentialsId: "fisgo-ci-github", url: "https://github.com/dreamkas/FisGo_CI.git", branch: "master"
    }

    sh "chmod +x ${env.WORKSPACE}/CI/bash_scripts/stage_start.sh"
    sh "chmod +x ${env.WORKSPACE}/CI/bash_scripts/stage_success.sh"
    sh "chmod +x ${env.WORKSPACE}/CI/bash_scripts/stage_failure.sh"
}

String getFisgoVersionFromConfig() {
    fisgoVerion = sh(returnStdout: true, script:"""grep -Po 'fisgo_cur_version = "\\K(.*[0-9])' ${env.WORKSPACE}/FisGo/src/appl/include/config.h""")
    return fisgoVerion.trim()
}

String getTags() {
    tags = sh(returnStdout: true, script:"cd FisGo ; git tag")
    return tags
}

String getMd5ofFile(String filePath) {
    md5Value = sh(returnStdout: true, script:"md5sum ${filePath} | cut -d ' ' -f 1")
    return md5Value
}