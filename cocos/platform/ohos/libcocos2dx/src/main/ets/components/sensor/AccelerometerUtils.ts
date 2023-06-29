import nativerender from "libnativerender.so";
//import Ability from '@ohos.application.Ability';
import { ContextType } from "../common/Constants"
import window from '@ohos.window';
import sensor from '@ohos.sensor';

const accUtils = nativerender.getContext(ContextType.ACCELERATOR_API);

export default class Accelerometer {

    private static instance = new Accelerometer();

    static getInstance() : Accelerometer {
        return Accelerometer.instance;
    }

    static init() : void {
        try {
            sensor.on(sensor.SensorId.ACCELEROMETER, function (data) {
                //在横屏状态下，对调xy轴
                accUtils.onSensorChangedCallBack(data.y, -data.x, data.z, 10000000);
            }, { interval: 10000000 });
        } catch (err) {
            console.error('On fail, errCode: ' + err.code + ' ,msg: ' + err.message);
        }
    }

}


globalThis.AccelerometerUtils = {};