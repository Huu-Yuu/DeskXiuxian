import QtQuick 2.0
import QtMultimedia 5.0

Item {
    id: media_player_frame

    property int index: 0
    //播放控制(取值：停止：0,播放：1,暂停：2)
    property int play_ctrl: -1
    property int border_width: 1
    property int playback_state: MediaPlayer.StoppedState
    property int duration: media_player.duration
    property int position: media_player.position

    property string border_color: "#000000"

    property alias media_source: media_player.source
    property alias background_color: background.color

    signal sendErrorInfo(int error_code, string error_string)
    signal sendPlayBackStatusChanged(int playback_state)

    Rectangle {
        id: background
        border.width: border_width
        border.color: border_color
        anchors.fill: parent
        color: "#FFFFFFFF"
    }

    MediaPlayer {
        id: media_player
        //        seekable: true
        onError: {
            sendErrorInfo(error, errorString)
        }
        onPlaybackStateChanged: {
            playback_state = media_player.playbackState
            sendPlayBackStatusChanged(playback_state)
        }
    }

    VideoOutput {
        anchors.fill: parent
        anchors.leftMargin: border_width
        anchors.rightMargin: border_width
        anchors.topMargin: border_width
        anchors.bottomMargin: border_width
        source: media_player
    }

    MouseArea {
        id: play_area
        enabled: media_player_frame.visible
        anchors.fill: parent
        onPressed: {
            if (media_player.playbackState === MediaPlayer.PlayingState) {
                media_player.stop()
            } else {
                media_player.play()
            }
        }
    }

    function setPosition(set_position) {
        media_player.seek(set_position)
    }

    onPlay_ctrlChanged: {
        if (play_ctrl == -1) {
            return
        }

        if (play_ctrl == 1) {
            //console.log("media_source:", media_source);
            media_player.play()
        } else if (play_ctrl == 2) {
            media_player.pause()
        } else {
            if (playback_state === MediaPlayer.PlayingState) {
                media_player.stop()
            }
        }
        //还原信号捕捉状态
        play_ctrl = -1
    }
}
