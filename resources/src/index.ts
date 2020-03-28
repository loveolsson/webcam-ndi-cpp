import axios, {CancelTokenSource} from 'axios'
import $ from 'jquery'
import {URLParam} from './urlparam';
import {ValueInfo} from './valueinfo';

function UpdateValueElement(elem: JQuery<HTMLElement>, valueInfo?: ValueInfo) {
  if (!valueInfo) {
    return;
  }

  if (valueInfo.numInt !== undefined && Number.isFinite(valueInfo.numInt)) {
    if (valueInfo.minInt !== undefined && Number.isFinite(valueInfo.minInt)) {
      if (elem.attr('min') != valueInfo.minInt.toString()) {
        elem.attr('min', valueInfo.minInt);
      }
    }

    if (valueInfo.maxInt !== undefined && Number.isFinite(valueInfo.maxInt)) {
      if (elem.attr('max') != valueInfo.maxInt.toString()) {
        elem.attr('max', valueInfo.maxInt);
      }
    }

    if (elem.val() != valueInfo.numInt) {
      elem.val(valueInfo.numInt);
    }

  } else if (valueInfo.str !== undefined) {
  }
}

class MainClass {
  cancelToken: CancelTokenSource = axios.CancelToken.source();
  readonly someRange: JQuery<HTMLElement>;

  constructor(private i: number) {
    this.someRange = $('#someRange').change(this.SetSomeRange.bind(this));

    this.RegularUpdate();
  }

  private SetSomeRange() {
    const payload = {data: this.someRange.val() ?.toString() };
    this.PostJson(`/${this.i}/settings`, payload);
  }

  private async PostJson(url: string, payload: any) {
    this.cancelToken.cancel();
    this.cancelToken = axios.CancelToken.source();

    try {
      const {data} = await axios.post(
          url, JSON.stringify(payload),
          {headers: {'Content-Type': 'application/json'}});
      console.log('Successfull set', data);
    } catch (e) {
      console.error('Set value failed', e);
    }
  }

  private ParseUpdateData(data: any) {
    if (typeof data !== 'object') {
      return;
    }

    UpdateValueElement(this.someRange, data.someRange);
  };

  private async RegularUpdate() {
    try {
      const {data} = await axios.get(
          `/${this.i}/settings`, {cancelToken: this.cancelToken.token});
      if (!data || typeof data !== 'object') {
        throw new Error('Bad data');
      }

      this.ParseUpdateData(data);
      setTimeout(this.RegularUpdate.bind(this), 2000);
    } catch (e) {
      setTimeout(this.RegularUpdate.bind(this), 10000);
    }
  }
}

$(() => {
  const cameraIndex = parseInt(URLParam('index')?.toString() || '0');
  if (Number.isFinite(cameraIndex)) {
    console.log(`Page loaded for camera ${cameraIndex}`);
    new MainClass(cameraIndex);
  } else {
    console.error('Bad camera index');
  }
});
